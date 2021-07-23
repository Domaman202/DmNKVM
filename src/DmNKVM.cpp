#include <DmNKVM.hpp>
#include <DmNSTD.hpp>
#include <cstdint>
#include <cstring>
#include <malloc.h>

using namespace DmN::std;

namespace DmN::KVM {
    /// Хрень которая содержит имя
    struct Nameble {
        uint32_t name;
    };

    /// String and ID
    struct SaI : Node<char> {
        SaI(char* name, uint32_t id, SaI* next) : Node<char>(name, next) {
            this->id = id;
        }

        uint32_t id;
        SaI* next;
    };

    /// Хренилище строк
    class StringStorage {
        SaI* start_node;

        /// Добавляет новую строку без проверки её существования, возвращает ID добавлянной строки
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

        /// Добавляет новую строку если она не существует, возвращает ID этой строки
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

        /// Получает имя по ID
        char* getName(uint32_t id) {
            // Перебираем ноды
            SaI* last_node = start_node;
            for (; id > 0; --id)
                last_node = last_node->next;
            // Возвращаем строку полученную по ID
            return last_node->value;
        }

        /// Получаем ID по имени
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

        /// Удаляем имя из списка по ID и возвращает само имя
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
            free(node_for_remove->value);
            free(node_for_remove);
            // Возвращаем строку
            return name;
        }

        /// Удаляет имя из списка и возвращает ID
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

    /// Универсальная основа классов
    struct Class_base : Nameble {
        /// Массив полей
        Field_t** fields;
        /// Массив методов
        Method_t** methods;
        /// Предки
        Class_base** parents;
        /// Кол-во предков
        uint8_t parents_size : 5;
        /// (Low Level Type) низкоуровнивый тип обьякта: PUBLIC, ENUM, STRUCT, CLASS
        uint8_t llt : 3;
    };

    /// 8-и основа классов
    struct Class_base_8bit : Class_base {
        /// Кол-во полей
        uint8_t fields_size;
        /// Кол-во методов
        uint8_t methods_size;
    };

    /// 16-ти битная основа классов
    struct Class_base_16bit : Class_base_8bit {
        /// Кол-во полей
        uint16_t fields_size;
        /// Кол-во методов
        uint16_t methods_size;
    };

    /// 32-х битная основа классов
    struct Class_base_32bit : Class_base_16bit {
        /// Кол-во полей
        uint32_t fields_size;
        /// Кол-во методов
        uint32_t methods_size;
    };

    /// 64-х битная основа классов
    struct Class_base_64bit : Class_base_32bit {
        /// Кол-во полей
        uint64_t fields_size;
        /// Кол-во методов
        uint64_t methods_size;
    };

    /// Поле
    struct Field_t : Nameble {
        Variable_t* value;
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

    /// Переменная
    struct Variable_t : Nameble, GC_Object {
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