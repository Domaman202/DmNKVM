#include "DmNSTD.hpp"
#include <stdint.h>

namespace DmN::KVM {
    ///
    struct Nameble { char* name; };
    ///
    struct Type_t;
    ///
    struct Enum_t;
    struct Struct_t;
    struct Class_t;
    ///
    struct Typeble { virtual Type_t* getType() = NULL; };
    ///
    struct Variable_t : Nameble, Typeble { void* value; };
    struct Field_t;
    struct Method_t;
}