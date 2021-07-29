#pragma once
#ifndef DMNKVM_JAVAPARSER_HPP
#define DMNKVM_JAVAPARSER_HPP

#include <cstdio>

#define CONSTANT_Utf8 1
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_Class 7
#define CONSTANT_String 8
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_NameAndType 12
#define CONSTANT_MethodHandle 15
#define CONSTANT_MethodType 16
#define CONSTANT_InvokeDynamic 18
#define CONSTANT_Module 19
#define CONSTANT_Package 20

#define JAVA_CLASSFILE_MAGIC              0xCAFEBABE
#define JAVA_MIN_SUPPORTED_VERSION        45
#define JAVA_MAX_SUPPORTED_VERSION        53
#define JAVA_MAX_SUPPORTED_MINOR_VERSION  0

// Used for two backward compatibility reasons:
// - to check for new additions to the class file format in JDK1.5
// - to check for bug fixes in the format checker in JDK1.5
#define JAVA_1_5_VERSION                  49
// Used for backward compatibility reasons:
// - to check for javac bug fixes that happened after 1.5
// - also used as the max version when running in jdk6
#define JAVA_6_VERSION                    50
// Used for backward compatibility reasons:
// - to disallow argument and require ACC_STATIC for <clinit> methods
#define JAVA_7_VERSION                    51
// Extension method support.
#define JAVA_8_VERSION                    52
//
#define JAVA_9_VERSION                    53

#define CP_OK 0 // 操作成功
#define CP_NO_DATA (-1) // 没有数据
#define CP_NO_INIT (-2) // 未初始化
#define CP_NO_MEM (-3) //申请内存出错
#define CP_PARSE_CONSTANTS_ERROR (-4) // 解析常量池错误

namespace DmN::KVM::JP {
    typedef unsigned char u1;
    typedef unsigned short u2;
    typedef unsigned int u4;
    typedef unsigned long long u8;

    typedef struct {
        u1 type;
        void *vp;
    } CONSTANT_ENTITY;

    typedef struct {
        u1 tag;
        u2 length;
        unsigned char *bytes;    // 获取到长度的时候再进行初始化
    } CONSTANT_Utf8_info;


    typedef struct {
        u1 tag;
        u4 bytes;
    } CONSTANT_Integer_info;

    typedef struct {
        u1 tag;
        u4 bytes;
    } CONSTANT_Float_info;

    typedef struct {
        u1 tag;
        u4 high_bytes;
        u4 low_bytes;
    } CONSTANT_Long_info;


    typedef struct {
        u1 tag;
        u4 high_bytes;
        u4 low_bytes;
    } CONSTANT_Double_info;


    typedef struct {
        u1 tag;
        u2 name_index;
    } CONSTANT_Class_info;

    typedef struct {
        u1 tag;
        u2 string_index;
    } CONSTANT_String_info;

    typedef struct {
        u1 tag;
        u2 class_index;
        u2 name_and_type_index;
    } CONSTANT_Fieldref_info;

    typedef struct {
        u1 tag;
        u2 class_index;
        u2 name_and_type_index;
    } CONSTANT_Methodref_info;

    typedef struct {
        u1 tag;
        u2 class_index;
        u2 name_and_type_index;
    } CONSTANT_InterfaceMethodref_info;

    typedef struct {
        u1 tag;
        u2 name_index;
        u2 descriptor_index;
    } CONSTANT_NameAndType_info;

    typedef struct {
        u1 tag;
        u1 reference_kind;
        u2 reference_index;
    } CONSTANT_MethodHandle_info;

    typedef struct {
        u1 tag;
        u2 descriptor_index;
    } CONSTANT_MethodType_info;

    typedef struct {
        u1 tag;
        u2 bootstrap_method_attr_index;
        u2 name_and_type_index;
    } CONSTANT_InvokeDynamic_info;

    typedef struct {
        u2 attribute_name_index;
        u4 attribute_length;
        u1 *info;//info[attribute_length]
    } Attribute_info;

    typedef struct {
        u2 access_flags;
        u2 name_index;
        u2 descriptor_index;
        u2 attributes_count;
        Attribute_info *attributes;
    } Method_info;


    typedef struct {
        u2 access_flags;
        u2 name_index;
        u2 descriptor_index;
        u2 attributes_count;
        Attribute_info *attributes;
    } Field_info;

    typedef struct {
        u4 magic;
        u2 minor_version;
        u2 major_version;
        u2 constant_pool_count;
        CONSTANT_ENTITY *constant_pool; // 常量池
        u2 access_flags;
        u2 this_class;
        u2 super_class;
        u2 interfaces_count;
        u2 *interfaces;
        u2 fields_count;
        Field_info *fields;
        u2 methods_count;
        Method_info *methods;
        u2 attributes_count;
        Attribute_info *attributes;
    } Java_class;

    typedef struct {
        FILE *fp;
        size_t len;
        size_t size;
        Java_class *aClass;
    } Java_class_file;


    //打开并初始化，path为class文件的路经，Java_class_file
    Java_class_file *class_open(const char *path);
    int class_parse(Java_class_file *classfile);
    int do_parse(Java_class_file *classfile, unsigned char *data);

    u2 swap_u2(u2 x);
    u4 swap_u4(u4 x);
    u8 swap_u8(u8 x);
}

#endif /* DMNKVM_JAVAPARSER_HPP */