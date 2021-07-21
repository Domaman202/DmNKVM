#include "DmNSTD.hpp"
#include <stdint.h>

namespace DmN::KVM {
    /// То что может иметь имя
    struct Nameble;
    /// То что может хранить значение
    struct Variable;
    /// То что имеет тип
    struct Typeble;
    /// То что наследуеться
    struct Extendable;
    /// То что хранит поля/методы
    struct FieldStorage;
    struct MethodStorage;
    /// Поле
    struct Field_t;
    /// Метод
    struct Method_t;
    /// Тип
    struct Type_t;
    /// Структура
    struct Struct_t;
}