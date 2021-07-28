#include <JavaParser.hpp>
#include <malloc.h>
#include <cstring>

namespace DmN::KVM::JP {
    CLASSFILE *class_open(const char *path) {
        CLASSFILE *classfile;
        classfile = (CLASSFILE *) malloc(sizeof(CLASSFILE));
        if (nullptr == classfile) {
            printf("申请内存空间出错!\n");
            return nullptr;
        }

        if ((classfile->fp = fopen(path, "rb")) == nullptr) {
            printf("打开%s出错!\n", path);
            return nullptr;
        }

        classfile->len = 0;
        classfile->aClass = nullptr;

        return classfile;
    }

    int class_parse(CLASSFILE *classfile) {
        unsigned char *data; // class文件内容
        long file_len; // class文件长度
        int res_code;

        if (fseek(classfile->fp, 0L, SEEK_END) != 0)
            return CP_NO_INIT;
        file_len = ftell(classfile->fp);
        rewind(classfile->fp);
        data = (unsigned char *) malloc(sizeof(char) * file_len);
        if (nullptr == data) {
            printf("NO_MEMORY!");
            return CP_NO_MEM;
        }
//    data[file_len]='\0';
        fread(data, file_len, 1, classfile->fp);
        fclose(classfile->fp);
        classfile->aClass = (CLASS *) malloc(sizeof(CLASS));
        if (nullptr == classfile->aClass) {
            printf("CP_NO_MEM");
            return CP_NO_MEM;
        }
        res_code = do_parse(classfile, data);
        free(data);
        return res_code;
    }


    int do_parse(CLASSFILE *classfile, unsigned char *data) {
        //结果值
        int rescode = CP_OK;
        // 魔数
        classfile->aClass->magic = swap_u4(*(u4 *) data);
        // minor_version
        data += sizeof(u4);
        classfile->aClass->minor_version = swap_u2(*(u2 *) data);
        data += sizeof(u2);
        classfile->aClass->major_version = swap_u2(*(u2 *) data);
        data += sizeof(u2);
        // 常量池大小
        classfile->aClass->constant_pool_count = swap_u2(*(u2 *) data);
        // 获取到常量池大小后向前移动两个字节
        data += sizeof(u2);
        // 分配常量池内存
        if (0 != classfile->aClass->constant_pool_count)
            classfile->aClass->constant_pool = (CONSTANT_ENTITY *) malloc(
                    sizeof(CONSTANT_ENTITY) * classfile->aClass->constant_pool_count);


        for (u2 i = 1; i < classfile->aClass->constant_pool_count; i++) {

            u1 element_type = *data;
            // 封装常量池实例
            auto *constant_entity = (CONSTANT_ENTITY *) malloc(sizeof(CONSTANT_ENTITY));
            constant_entity->type = element_type;
            switch (element_type) {
                case CONSTANT_Utf8: {
                    auto *constant_utf8_info = (CONSTANT_Utf8_info *) malloc(sizeof(CONSTANT_Utf8_info));
                    constant_utf8_info->tag = element_type;
                    data++;
                    constant_utf8_info->length = swap_u2(*(u2 *) data);
                    data += sizeof(u2);
                    constant_utf8_info->bytes = (unsigned char *) malloc(constant_utf8_info->length);
                    memset(constant_utf8_info->bytes, 0, constant_utf8_info->length);
                    for (int j = 0; j < constant_utf8_info->length; j++) {
                        constant_utf8_info->bytes[j] = *(u1 *) data;
                        data++;
                    }
                    constant_entity->vp = constant_utf8_info;
                    break;
                }
                case CONSTANT_Integer: {
                    auto *constant_integer_info = (CONSTANT_Integer_info *) malloc(sizeof(CONSTANT_Integer_info));
                    constant_integer_info->tag = element_type;
                    data++;
                    constant_integer_info->bytes = swap_u4(*(u4 *) data);
                    data += sizeof(u4);
                    constant_entity->vp = constant_integer_info;
                    break;
                }
                case CONSTANT_Float: {
                    auto *constant_float_info = (CONSTANT_Float_info *) malloc(sizeof(CONSTANT_Float_info));
                    constant_float_info->tag = element_type;
                    data++;
                    constant_float_info->bytes = swap_u4(*(u4 *) data);
                    data += sizeof(u4);
                    constant_entity->vp = constant_float_info;
                    break;
                }
                case CONSTANT_Long: {
                    auto *constant_long_info = (CONSTANT_Long_info *) malloc(sizeof(CONSTANT_Long_info));
                    constant_long_info->tag = element_type;
                    data++;
                    constant_long_info->high_bytes = swap_u4(*(u4 *) data);
                    data += sizeof(u4);
                    constant_long_info->low_bytes = swap_u4(*(u4 *) data);
                    data += sizeof(u4);
                    constant_entity->vp = constant_long_info;
                    // Long 和 Double占两个常量池位
                    classfile->aClass->constant_pool[i] = *constant_entity;
                    i++;
                    continue;
                }
                case CONSTANT_Double: {
                    auto *constant_double_info = (CONSTANT_Double_info *) malloc(sizeof(CONSTANT_Double_info));
                    constant_double_info->tag = element_type;
                    data++;
                    constant_double_info->high_bytes = swap_u4(*(u4 *) data);
                    data += sizeof(u4);
                    constant_double_info->low_bytes = swap_u4(*(u4 *) data);
                    data += sizeof(u4);
                    constant_entity->vp = constant_double_info;

                    classfile->aClass->constant_pool[i] = *constant_entity;
                    i++;
                    continue;
                }
                case CONSTANT_Class: {
                    auto *constant_class_info = (CONSTANT_Class_info *) malloc(sizeof(CONSTANT_Class_info));
                    constant_class_info->tag = element_type;
                    data++;
                    constant_class_info->name_index = swap_u2(*(u2 *) data);
                    data += sizeof(u2);
                    constant_entity->vp = constant_class_info;
                    break;
                }
                case CONSTANT_String: {
                    auto *constant_string_info = (CONSTANT_String_info *) malloc(sizeof(CONSTANT_String_info));
                    constant_string_info->tag = element_type;
                    data++;
                    constant_string_info->string_index = swap_u2(*(u2 *) data);
                    data += sizeof(u2);
                    constant_entity->vp = constant_string_info;
                    break;
                }
                case CONSTANT_Fieldref: {
                    auto *constant_fieldref_info = (CONSTANT_Fieldref_info *) malloc(sizeof(CONSTANT_Fieldref_info));
                    constant_fieldref_info->tag = element_type;
                    data++;
                    constant_fieldref_info->class_index = swap_u2(*(u2 *) data);
                    data += sizeof(u2);
                    constant_fieldref_info->name_and_type_index = swap_u2(*(u2 *) data);
                    data += sizeof(u2);
                    constant_entity->vp = constant_fieldref_info;
                    break;
                }
                case CONSTANT_Methodref: {
                    auto *constant_methodref_info = (CONSTANT_Methodref_info *) malloc(sizeof(CONSTANT_Methodref_info));
                    constant_methodref_info->tag = element_type;
                    data++;
                    constant_methodref_info->class_index = swap_u2(*(u2 *) data);
                    data += sizeof(u2);
                    constant_methodref_info->name_and_type_index = swap_u2(*(u2 *) data);
                    data += sizeof(u2);
                    constant_entity->vp = constant_methodref_info;
                    break;
                }
                case CONSTANT_InterfaceMethodref: {
                    auto *constant_interfaceMethodref_info = (CONSTANT_InterfaceMethodref_info *) malloc(
                            sizeof(CONSTANT_InterfaceMethodref_info));
                    constant_interfaceMethodref_info->tag = element_type;
                    data++;
                    constant_interfaceMethodref_info->class_index = swap_u2(*(u2 *) data);
                    data += sizeof(u2);
                    constant_interfaceMethodref_info->name_and_type_index = swap_u2(*(u2 *) data);
                    data += sizeof(u2);
                    constant_entity->vp = constant_interfaceMethodref_info;
                    break;
                }
                case CONSTANT_NameAndType: {
                    auto *constant_nameAndType_info = (CONSTANT_NameAndType_info *) malloc(
                            sizeof(CONSTANT_NameAndType_info));
                    constant_nameAndType_info->tag = element_type;
                    data++;
                    constant_nameAndType_info->name_index = swap_u2(*(u2 *) data);
                    data += sizeof(u2);
                    constant_nameAndType_info->descriptor_index = swap_u2(*(u2 *) data);
                    data += sizeof(u2);
                    constant_entity->vp = constant_nameAndType_info;
                    break;
                }
                case CONSTANT_MethodHandle: {
                    auto *constant_methodHandle_info = (CONSTANT_MethodHandle_info *) malloc(
                            sizeof(CONSTANT_MethodHandle_info));
                    constant_methodHandle_info->tag = element_type;
                    data++;
                    constant_methodHandle_info->reference_kind = *(u1 *) data;
                    data += sizeof(u1);
                    constant_methodHandle_info->reference_index = swap_u2(*(u2 *) data);
                    data += sizeof(u2);
                    constant_entity->vp = constant_methodHandle_info;
                    break;
                }
                case CONSTANT_MethodType: {
                    auto *constant_methodType_info = (CONSTANT_MethodType_info *) malloc(
                            sizeof(CONSTANT_MethodType_info));
                    constant_methodType_info->tag = element_type;
                    data++;
                    constant_methodType_info->descriptor_index = swap_u2(*(u2 *) data);
                    data += sizeof(u2);
                    constant_entity->vp = constant_methodType_info;
                    break;
                }
                case CONSTANT_InvokeDynamic: {
                    auto *constant_invokeDynamic_info = (CONSTANT_InvokeDynamic_info *) malloc(
                            sizeof(CONSTANT_InvokeDynamic_info));
                    constant_invokeDynamic_info->tag = element_type;
                    data++;
                    constant_invokeDynamic_info->bootstrap_method_attr_index = swap_u2(*(u2 *) data);
                    data += sizeof(u2);
                    constant_invokeDynamic_info->name_and_type_index = swap_u2(*(u2 *) data);
                    data += sizeof(u2);
                    constant_entity->vp = constant_invokeDynamic_info;
                    break;
                }
                case CONSTANT_Module:
                    break;
                case CONSTANT_Package:
                    break;
                default:
                    return CP_PARSE_CONSTANTS_ERROR;
            }
            classfile->aClass->constant_pool[i] = *constant_entity;

        }

        classfile->aClass->access_flags = swap_u2(*(u2 *) data);
        data += sizeof(u2);
        classfile->aClass->this_class = swap_u2(*(u2 *) data);
        data += sizeof(u2);
        classfile->aClass->super_class = swap_u2(*(u2 *) data);
        data += sizeof(u2);
        classfile->aClass->interfaces_count = swap_u2(*(u2 *) data);
        data += sizeof(u2);
        if (classfile->aClass->interfaces_count > 0) {
            classfile->aClass->interfaces = (u2 *) malloc(sizeof(u2) * classfile->aClass->interfaces_count);
            for (int f = 0; f < classfile->aClass->interfaces_count; f++) {
                classfile->aClass->interfaces[f] = swap_u2(*(u2 *) data);
                data += sizeof(u2);
            }
        }
        classfile->aClass->fields_count = swap_u2(*(u2 *) data);
        data += sizeof(u2);

        // 解析字段
        if (classfile->aClass->fields_count > 0) {
            classfile->aClass->fields = (field_info *) malloc(sizeof(field_info) * classfile->aClass->fields_count);
            for (int i = 0; i < classfile->aClass->fields_count; i++) {
                classfile->aClass->fields[i].access_flags = swap_u2(*(u2 *) data);
                data += sizeof(u2);
                classfile->aClass->fields[i].name_index = swap_u2(*(u2 *) data);
                data += sizeof(u2);
                classfile->aClass->fields[i].descriptor_index = swap_u2(*(u2 *) data);
                data += sizeof(u2);
                classfile->aClass->fields[i].attributes_count = swap_u2(*(u2 *) data);
                data += sizeof(u2);
                if (classfile->aClass->fields[i].attributes_count > 0) {
                    classfile->aClass->fields[i].attributes = (attribute_info *) malloc(
                            sizeof(attribute_info) * classfile->aClass->fields[i].attributes_count);
                    for (int m = 0; m < classfile->aClass->fields[i].attributes_count; m++) {
                        classfile->aClass->fields[i].attributes[m].attribute_name_index = swap_u2(*(u2 *) data);
                        data += sizeof(u2);
                        classfile->aClass->fields[i].attributes[m].attribute_length = swap_u4(*(u4 *) data);
                        data += sizeof(u4);
                        if (classfile->aClass->fields[i].attributes[m].attribute_length > 0) {
                            classfile->aClass->fields[i].attributes[m].info = (u1 *) malloc(
                                    sizeof(u1) * classfile->aClass->fields[i].attributes[m].attribute_length);
                            for (int n = 0; n < classfile->aClass->fields[i].attributes[m].attribute_length; n++) {
                                classfile->aClass->fields[i].attributes[m].info[n] = *(u1 *) data;
                                data += sizeof(u1);
                            }
                        }
                    }
                }
            }
        }

        classfile->aClass->methods_count = swap_u2(*(u2 *) data);
        data += sizeof(u2);

        // parse methods
        if (classfile->aClass->methods_count > 0) {
            classfile->aClass->methods = (method_info *) malloc(sizeof(method_info) * classfile->aClass->methods_count);
            for (int i = 0; i < classfile->aClass->methods_count; i++) {
                classfile->aClass->methods[i].access_flags = swap_u2(*(u2 *) data);
                data += sizeof(u2);
                classfile->aClass->methods[i].name_index = swap_u2(*(u2 *) data);
                data += sizeof(u2);
                classfile->aClass->methods[i].descriptor_index = swap_u2(*(u2 *) data);
                data += sizeof(u2);
                classfile->aClass->methods[i].attributes_count = swap_u2(*(u2 *) data);
                data += sizeof(u2);
                if (classfile->aClass->methods[i].attributes_count > 0) {
                    classfile->aClass->methods[i].attributes = (attribute_info *) malloc(
                            sizeof(attribute_info) * classfile->aClass->methods[i].attributes_count);
                    for (int m = 0; m < classfile->aClass->methods[i].attributes_count; m++) {
                        classfile->aClass->methods[i].attributes[m].attribute_name_index = swap_u2(*(u2 *) data);
                        data += sizeof(u2);
                        classfile->aClass->methods[i].attributes[m].attribute_length = swap_u4(*(u4 *) data);
                        data += sizeof(u4);
                        if (classfile->aClass->methods[i].attributes[m].attribute_length > 0) {
                            classfile->aClass->methods[i].attributes[m].info = (u1 *) malloc(
                                    sizeof(u1) * classfile->aClass->methods[i].attributes[m].attribute_length);
                            for (int n = 0; n < classfile->aClass->methods[i].attributes[m].attribute_length; n++) {
                                classfile->aClass->methods[i].attributes[m].info[n] = *(u1 *) data;
                                data += sizeof(u1);
                            }
                        }
                    }
                }
            }
        }

        classfile->aClass->attributes_count = swap_u2(*(u2 *) data);
        data += sizeof(u2);
        // parse attributes
        if (classfile->aClass->attributes_count > 0) {
            classfile->aClass->attributes = (attribute_info *) malloc(
                    sizeof(attribute_info) * classfile->aClass->attributes_count);
            for (int m = 0; m < classfile->aClass->attributes_count; m++) {
                classfile->aClass->attributes->attribute_name_index = swap_u2(*(u2 *) data);
                data += sizeof(u2);
                classfile->aClass->attributes->attribute_length = swap_u4(*(u4 *) data);
                data += sizeof(u4);
                if (classfile->aClass->attributes->attribute_length > 0) {
                    classfile->aClass->attributes->info = (u1 *) malloc(
                            sizeof(u1) * classfile->aClass->attributes->attribute_length);
                    for (int n = 0; n < classfile->aClass->attributes->attribute_length; n++) {
                        classfile->aClass->attributes->info[n] = *(u1 *) data;
                        data += sizeof(u1);
                    }
                }
            }
        }

        return rescode;
    }

    inline u2 swap_u2(u2 x) {
        return ((x & 0x00ff) << 8) | ((x & 0xff00) >> 8);
    }

    inline u4 swap_u4(u4 x) {
        return ((x & 0x000000ff) << 24) |
               ((x & 0x0000ff00) << 8) |
               ((x & 0x00ff0000) >> 8) |
               ((x & 0xff000000) >> 24);
    }

    inline u8 swap_u8(u8 x) {
        return ((x & 0x00000000000000ff) << 56) |
               ((x & 0x000000000000ff00) << 40) |
               ((x & 0x0000000000ff0000) << 24) |
               ((x & 0x00000000ff000000) << 8) |
               ((x & 0x000000ff00000000) >> 8) |
               ((x & 0x0000ff0000000000) >> 24) |
               ((x & 0x00ff000000000000) >> 40) |
               ((x & 0xff00000000000000) >> 56);
    }
}