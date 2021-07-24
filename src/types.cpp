#include <types.hpp>
#include <DmNSTD.hpp>
#include <cstdint>
#include <cstring>
#include <malloc.h>

using namespace DmN::std;

namespace DmN::KVM {
    /// Хрень которая содержит имя
    struct Nameble {
        explicit Nameble(uint32_t name) {
            this->name = name;
        }

        /// ID имени
        uint32_t name;
    };

    /// String and ID
    struct SaI : Node<char> {
        SaI(char* name, uint32_t id, SaI* next) : Node<char>(name, next) {
            this->id = id;
            this->next = next;
        }

        /// ID
        uint32_t id;
        /// Следующий объект
        SaI* next;
    };

    /// Хренилище строк
    class StringStorage {
        /// Первая нода (всегда пуста)
        SaI* start_node;

        /*!
         * Добавляет новую строку без проверки её существования, возвращает ID добавлянной строки
         * \param name - имя которое нужно добавить
         * \return ID которое принадлежит имени
         */
        uint32_t addNewName(char* name) {
            // Перебираем ноды
            SaI* last_node = start_node;
            while (last_node->next != nullptr)
                last_node = last_node->next;
            // Пихаем новую ноду с новой строкой
            last_node->next = new SaI(name, last_node->id++, nullptr);
            // Возвращаем ID новой строки
            return last_node->next->id;
        }

        /*!
         * Добавляет новую строку если она не существует, возвращает ID этой строки
         * \param name - имя которое нужно добавить
         * \return ID которое принадлежит имени
         */
        uint32_t addName(char* name) {
            // Перебираем ноды
            SaI* last_node = start_node;
            while (last_node->next != nullptr) {
                // Проверяем на существование имени
                if (strcmp(last_node->value, name) == 0)
                    // Возвращаем ID этого имени
                    return last_node->id;
                // Перебираем ноды
                last_node = last_node->next;
            }
            // Проверяем на существование строки
            if (strcmp(last_node->value, name) == 0)
                // Возвращаем ID этой строки
                return last_node->id;
            // Пихаем новую ноду с новой строкой
            last_node->next = new SaI(name, last_node->id++, nullptr);
            // Возвращаем ID новой строки
            return last_node->next->id;
        }

        /*!
         * Получает имя по ID
         * \param id - ID по которому мы получаем имя
         * \return Имя полученное по ID
         */
        char* getName(uint32_t id) {
            // Перебираем ноды
            SaI* last_node = start_node;
            for (; id > 0; --id)
                last_node = last_node->next;
            // Возвращаем строку полученную по ID
            return last_node->value;
        }

        /*!
         * Получаем ID по имени
         * \param name - имя ID которого нужно получить
         * \return ID этого имени
         */
        uint32_t getId(char* name) {
            // Перебираем ноды
            SaI* last_node = start_node;
            while (last_node != nullptr) {
                // Сравниваем имена
                if (strcmp(last_node->value, name) == 0)
                    // Если строки совпадают то возвращаем нужный ID
                    return last_node->id;
                // Перебираем ноды дальше
                last_node = last_node->next;
            }
            // Если нихрена не нашли то возвращаем 0
            return 0;
        }

        /*!
         * Удаляем имя из списка по ID и возвращает само имя
         * \param id ID которое нужно удалить
         * \return имя которое было удалено
         */
        char* remove(uint32_t id) {
            // Перебираем ноды
            SaI* last_node = start_node;
            for (; id > 0; id--)
                last_node = last_node->next;
            // Получаем ноду строки для удаления
            SaI* node_for_remove = last_node->next;
            // Получаем строку
            char* name = node_for_remove->value;
            // Выпиливаем ноду из списка
            last_node->next = node_for_remove->next;
            // Высвобождаем память
            free(node_for_remove);
            // Возвращаем строку
            return name;
        }

        /*!
         * Удаляет имя из списка и возвращает ID
         * \param name - имя для удаления
         * \return ID удалённого имени
         */
        uint32_t remove(char* name) {
            // Перебираем ноды
            SaI* last_node = start_node;
            while (last_node != nullptr) {
                if (strcmp(last_node->next->value, name) == 0) {
                    // Получаем ноду строки для удаления
                    SaI* node_for_remove = last_node->next;
                    // Получаем ID
                    uint32_t i = node_for_remove->id;
                    // Выпиливаем ноду из списка
                    last_node->next = node_for_remove->next;
                    // Высвобождаем память
                    free(node_for_remove->value);
                    free(node_for_remove);
                    // Возвращаем ID
                    return i;
                }
                last_node = last_node->next;
            }
            // Если что-то пошло по одному месту то возвращаем 0
            return 0;
        }
    };

    /// Объект подвергающийся сборке мусора
    struct GC_Object {
        /// Собран ли объект?
        bool is_collected : 1;
        /// Можно ли собирать объект?
        bool is_collectable : 1;
        /// Кол-во ссылок на объект
        uint16_t references : 10;
    };

    struct LLT {
        explicit LLT(uint8_t llt) {
            this->llt = llt;
        }
        /// (Low Level Type) низкоуровнивый тип обьякта: PUBLIC, ENUM, STRUCT, CLASS
        uint8_t llt : 3;
    };

    /// Универсальная основа для Enum-а
    struct Enum_base : LLT, Nameble {
        /// Перечисления
        Variable_t** enums;
        //
        const uint8_t llt : 3 = 1;
    };

    struct Enum_8bit_t : Enum_base {
        /// Кол-во перечислений
        uint8_t enums_size;
    };

    struct Enum_16bit_t : Enum_8bit_t {
        /// Кол-во перечислений
        uint16_t enums_size;
    };

    struct Enum_32bit_t : Enum_16bit_t {
        /// Кол-во перечислений
        uint32_t enums_size;
    };

    struct Struct_base : LLT, Nameble {
        /// Поля
        Field_t** fields;
        /// Предки
        Struct_base** parents;
        /// Кол-во предков
        uint8_t parents_size : 5;
        //
        const uint8_t llt : 3 = 2;
    };

    struct Struct_8bit_t : Struct_base {
        /// Кол-во полей
        uint8_t fields_size;
    };

    struct Struct_16bit_t : Struct_8bit_t {
        /// Кол-во полей
        uint16_t fields_size;
    };

    struct Struct_32bit_t : Struct_16bit_t {
        /// Кол-во полей
        uint32_t fields_size;
    };

    /// Универсальная основа для Class-а
    struct Class_base : LLT, Nameble {
        /// Массив полей
        Field_t** fields;
        /// Массив методов
        Method_t** methods;
        /// Предки
        Class_base** parents;
        /// Кол-во предков
        uint8_t parents_size : 5;
        //
        const uint8_t llt : 3 = 3;
    };

    struct Class_8bit_t : Class_base {
        /// Кол-во полей
        uint8_t fields_size;
        /// Кол-во методов
        uint8_t methods_size;
    };

    struct Class_16bit_t : Class_8bit_t {
        /// Кол-во полей
        uint16_t fields_size;
        /// Кол-во методов
        uint16_t methods_size;
    };

    struct Class_32bit_t : Class_16bit_t {
        /// Кол-во полей
        uint32_t fields_size;
        /// Кол-во методов
        uint32_t methods_size;
    };

    /// Поле
    struct Field_t : LLT, Nameble {
        Field_t(Value_t* value, uint32_t name) : LLT(0), Nameble(name) {
            this->value = value;
        }
        /// Значение
        Value_t* value;
    };

    /// Метод
    struct Method_t : Nameble {
        /// ID дескриптора
        uint32_t descriptor;
        /// Размер байт-кода
        uint32_t code_size;
        /// Байт-код
        uint8_t* code;
    };

    /// Значение
    struct Value_t : GC_Object {
        /// Тип значения: INT8 (1), INT16 (2), INT32 (3), INT64 (4), UINT8 (5), UINT16 (6), UINT32 (7), UINT64 (8), FLOAT (9), DOUBLE (10), CHAR (11), REFERENCE (12), OBJECT (13)
        uint8_t type : 4;
        /// Значение
        void* value;
    };

    /// Переменная
    struct Variable_t : Value_t, Nameble {
        /// Тип переменной: INT8 (1), INT16 (2), INT32 (3), INT64 (4), UINT8 (5), UINT16 (6), UINT32 (7), UINT64 (8), FLOAT (9), DOUBLE (10), CHAR (11), REFERENCE (12), OBJECT (13)
        uint8_t type : 4;
        /// Значение переменной
        void* value;
    };

    /// Лямбда
    struct Lambda_t : GC_Object {
        /// ID дескриптора
        uint32_t descriptor;
        /// Размер байт-кода
        uint32_t code_size;
        /// Байт-код
        uint8_t* code;
    };
}