#pragma once
#ifndef DMNKVM_KVMTYPES_HPP
#define DMNKVM_KVMTYPES_HPP

#include <DmNSTD.hpp>
#include <cstdint>

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
    struct SaI : std::Node<char> {
        SaI(char* name, uint32_t id, SaI* next) : Node<char>(name, next) {
            this->id = id;
            this->next = next;
        }

        /// ID
        uint32_t id;
        /// Следующий объект
        SaI* next;
    };

    /// Абстрактное хранилище строк
    class StringStorage {
    public:
        /*!
         * Добавляет новую строку без проверки её существования, возвращает ID добавлянной строки
         * \param name - имя которое нужно добавить
         * \return ID которое принадлежит имени
         */
        virtual uint32_t addNewName(char* name) = NULL;

        /*!
         * Добавляет новую строку если она не существует, возвращает ID этой строки
         * \param name - имя которое нужно добавить
         * \return ID которое принадлежит имени
         */
        virtual uint32_t addName(char* name) = NULL;

        /*!
         * Получает имя по ID
         * \param id - ID по которому мы получаем имя
         * \return Имя полученное по ID
         */
        virtual char* getName(uint32_t id) = NULL;

        /*!
         * Получаем ID по имени
         * \param name - имя ID которого нужно получить
         * \return ID этого имени
         */
        virtual uint32_t getId(char* name) = NULL;

        /*!
         * Удаляем имя из списка по ID и возвращает само имя
         * (Сохраняет ноду для переиспользования)
         * \param id ID которое нужно удалить
         * \return имя которое было удалено
         */
        virtual char* free(uint32_t id) = NULL;

        /*!
         * Удаляет имя из списка и возвращает ID
         * (Удаляет ноду)
         * \param name - имя для удаления
         * \return ID удалённого имени
         */
        virtual uint32_t free(const char* name) = NULL;

        /*!
         * Удаляем имя из списка по ID и возвращает само имя
         * (Удаляет ноду)
         * \param id ID которое нужно удалить
         * \return имя которое было удалено
         */
        virtual char* remove(uint32_t id) = NULL;

        /*!
         * Удаляет имя из списка и возвращает ID
         * (Удаляет ноду)
         * \param name - имя для удаления
         * \return ID удалённого имени
         */
        virtual uint32_t remove(const char* name) = NULL;

        /*!
         * Очищает данные
         */
        virtual void clear() = NULL;
    };

    /// Хренилище строк
    class DynamicStringStorage : StringStorage {
    public:
        /// Первая нода (всегда пуста)
        SaI* start_node = new SaI(nullptr, 0, nullptr);

        uint32_t addNewName(char* name) override;
        uint32_t addName(char* name) override;
        char * getName(uint32_t id) override;
        uint32_t getId(char *name) override;
        char * free(uint32_t id) override;
        uint32_t free(const char *name) override;
        char * remove(uint32_t id) override;
        uint32_t remove(const char *name) override;
        void clear() override;
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

    /// Хрень которая имеет низкоуровневый тип объекта
    struct LLT {
        explicit LLT(uint8_t llt) {
            this->llt = llt;
        }
        /// (Low Level Type) низкоуровневый тип обьякта: PUBLIC, ENUM, STRUCT, CLASS
        uint8_t llt : 3;
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
}

#endif /* DMNKVM_KVMTYPES_HPP */