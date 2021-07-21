#include "DmNKVM.hpp"

namespace DmN::KVM {
    ///
    struct Type_t : Nameble {
        // Modifier (PUBLIC, ENUM, STRUCT, CLASS)
        uint8_t modifier : 2;
        // Extends & extends count
        uint8_t extendsCount : 6;
        Type_t** extends;
        // GC
        uint8_t ref_count;

        virtual Field_t** getFields() = NULL;
        virtual Method_t** getMethods() = NULL;
    };
    ///
    struct Struct_t : Type_t {
        uint8_t fieldsCount;
        Field_t** fields;

        Field_t** getFields() override { return fields; };
    };

    struct Class_t : Struct_t {
        uint8_t methodsCount;
        Method_t** methods;

        Method_t** getMethods() override { return methods; }
    };
    ///
    struct Field_t : Typeble, Nameble {
        Type_t* type;
        Type_t* getType() override { return type; };
    };

    struct Method_t : Nameble {
        uint32_t length;
        int8_t** code;
    };
}