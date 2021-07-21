#include "DmNKVM.hpp"

namespace DmN::KVM {
    ///
    struct Nameble {
        char* name = nullptr;
    };
    ///
    struct Variable {
        void* value = nullptr;
    };
    ///
    struct Typeble {
        Type_t* type = nullptr;
    };
    ///
    struct Extendable {
        uint8_t extends_size : 5;
        Type_t** extends = nullptr;
    };
    ///
    struct FieldStorage {
        virtual Field_t** getFields() = NULL;
    };
    ///
    struct MethodStorage {
        virtual Method_t** getMethods() = NULL;
    };
    ///
    struct Type_t : Nameble, Extendable { };
    ///
    struct Struct_t : Type_t, FieldStorage, MethodStorage {
        Field_t** fields = nullptr;
        Method_t** methods = nullptr;
    };
}