#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_JP_HPP
#define DMN_KVM_JP_HPP

#include <KVMConfig.hpp>
#include <SDmNL.hpp>

using namespace DmN::SDL::Byte;

namespace DmN::KVM::JP {
    DMN_KVM_E struct CPInfo {
        u1 tag;

        union {
            struct {
                u2 name_index;
            } Class;

            struct {
                u2 class_index;
                u2 name_and_type_index;
            } Reference;

            struct {
                u2 name_index;
                u2 descriptor_index;
            } NameAndType;

            struct {
                u2 length;
                u1* bytes;
            } UTF8;

            struct {
                u2 string_index;
            } String;

            struct {
                u4 bytes;
            } IntegerFloat;

            struct {
                u4 hBytes;
                u4 lBytes;
            } LongDouble;
        } value;
    };

    DMN_KVM_E struct ExceptionTableType {
        u2 start_pc;
        u2 end_pc;
        u2 handler_pc;
        u2 catch_type;
    };

    DMN_KVM_E struct ClassesType {
        u2 inner_class_info_index;
        u2 outer_class_info_index;
        u2 inner_name_index;
        u2 inner_class_access_flags;
    };

    DMN_KVM_E struct LineNumberTableType {
        u2 start_pc;
        u2 line_number;
    };

    DMN_KVM_E struct LocalVariableTableType {
        u2 start_pc;
        u2 length;
        u2 name_index;
        u2 descriptor_index;
        u2 index;
    };

    DMN_KVM_E struct AttributeInfo {
        u2 attribute_name_index;
        u4 attribute_length;

        union {
            struct {
                u2 constant_value_index;
            } ConstantValue;

            struct {
                u2 max_stack;
                u2 max_locals;
                u4 code_length;
                u1* code;
                u2 exception_table_length;
                ExceptionTableType* exception_table;
                u2 attributes_count;
                AttributeInfo* attributes;
            } Code;

            struct { } Deprecated;

            struct {
                u2 number_of_exceptions;
                u2* exception_index_table;
            } Exceptions;

            struct {
                u2 number_of_classes;
                ClassesType* classes;
            } InnerClasses;

            struct {
                u2 line_number_table_length;
                LineNumberTableType* line_number_table;
            } LineNumberTable;

            struct {
                u2 local_variable_table_length;
                LocalVariableTableType* local_variable_table;
            } LocalVariableTable;

            struct { } Synthetic;

            struct {
                u2 sourcefile_index;
            } SourceFile;
        } value;
    };

    DMN_KVM_E struct FieldInfo {
        u2 access_flags;
        u2 name_index;
        u2 descriptor_index;
        u2 attributes_count;
        AttributeInfo* attributes;
    };

    DMN_KVM_E struct MethodInfo {
        u2 access_flags;
        u2 name_index;
        u2 descriptor_index;
        u2 attributes_count;
        AttributeInfo* attributes;
    };

    DMN_KVM_E struct ClassFile {
        u4 magic;

        u2 minor_version;
        u2 major_version;

        u2 constant_pool_count;
        CPInfo* constant_pool;

        u2 access_flags;

        u2 this_class;

        u2 super_class;

        u2 interfaces_count;
        u2* interfaces;

        u2 fields_count;
        FieldInfo* fields;

        u2 methods_count;
        MethodInfo* methods;

        u2 attributes_count;
        AttributeInfo* attributes;
    };
}

#endif /* DMN_KVM_JP_HPP */