#pragma once
#ifndef DMNKVM_KVMTYPES_HPP
#define DMNKVM_KVMTYPES_HPP

#include <KVMConfig.h>
#include <DmNSTD.hpp>
#include <JavaParser.hpp>
#include <malloc.h>
#include <cstdint>
#include <utility>

namespace DmN::KVM {
    /// String and ID
    struct SaI : std::Node<char> {
        SaI(char* name, SI_t id, SaI* next) : Node<char>(name, next) {
            this->id = id;
            this->next = next;
        }

        /// ID
        SI_t id;
        /// Следующий объект
        SaI* next;
    };

    /// Абстрактное хранилище строк
    struct StringStorage {
    public:
        /*!
         * Добавляет новую строку без проверки её существования, возвращает ID добавлянной строки
         * \param name - имя которое нужно добавить
         * \return ID которое принадлежит имени
         */
        virtual SI_t addNewName(const char* name) = NULL;

        /*!
         * Добавляет новую строку если она не существует, возвращает ID этой строки
         * \param name - имя которое нужно добавить
         * \return ID которое принадлежит имени
         */
        virtual SI_t addName(const char* name) = NULL;

        /*!
         * Получает имя по ID
         * \param id - ID по которому мы получаем имя
         * \return Имя полученное по ID
         */
        virtual const char* getName(SI_t id) = NULL;

        /*!
         * Получаем ID по имени
         * \param name - имя ID которого нужно получить
         * \return ID этого имени
         */
        virtual SI_t getId(const char* name) = NULL;

        /*!
         * Удаляем имя из списка по ID и возвращает само имя
         * (Сохраняет ноду для переиспользования)
         * \param id ID которое нужно удалить
         * \return имя которое было удалено
         */
        virtual const char* free(SI_t id) = NULL;

        /*!
         * Удаляет имя из списка и возвращает ID
         * (Удаляет ноду)
         * \param name - имя для удаления
         * \return ID удалённого имени
         */
        virtual SI_t free(const char* name) = NULL;

        /*!
         * Удаляем имя из списка по ID и возвращает само имя
         * (Удаляет ноду)
         * \param id ID которое нужно удалить
         * \return имя которое было удалено
         */
        virtual const char* remove(SI_t id) = NULL;

        /*!
         * Удаляет имя из списка и возвращает ID
         * (Удаляет ноду)
         * \param name - имя для удаления
         * \return ID удалённого имени
         */
        virtual SI_t remove(const char* name) = NULL;

        /*!
         * Очищает данные
         */
        virtual void clear() = NULL;
    };

    /// Статическое хранилище строк
    class StaticStringStorage : StringStorage {
    protected:
        /// Массив ID и строк
        const char** data;
        /// Размер
        size_t size;
        /// Текущий индекс
        size_t last_index = 0;
    public:
        explicit StaticStringStorage(size_t size) {
            this->data = static_cast<const char**>(calloc(size, sizeof(char*)));
            this->size = size;
        }

        SI_t addNewName(const char* name) override;
        SI_t addName(const char* name) override;
        const char* getName(SI_t id) override;
        SI_t getId(const char *name) override;
        const char* free(SI_t id) override;
        SI_t free(const char *name) override;
        const char* remove(SI_t id) override;
        SI_t remove(const char *name) override;
        void clear() override;
    };

    /// Динамическое хранилище строк
    class DynamicStringStorage : StringStorage {
    protected:
        /// Первая нода (всегда пуста)
        SaI* start_node = new SaI(nullptr, 0, nullptr);
    public:
        SI_t addNewName(const char* name) override;
        SI_t addName(const char* name) override;
        const char * getName(SI_t id) override;
        SI_t getId(const char *name) override;
        const char * free(SI_t id) override;
        SI_t free(const char *name) override;
        const char * remove(SI_t id) override;
        SI_t remove(const char *name) override;
        void clear() override;
    };

    /// Хрень которая содержит имя
    struct Nameble {
        explicit Nameble(SI_t name) {
            this->name = name;
        }

        /// ID имени
        SI_t name;
    };

    /// Хрень которая имеет низкоуровневый тип объекта
    struct LLT {
        explicit LLT(uint8_t llt) {
            this->llt = llt;
        }
        /// (Low Level Type) низкоуровневый тип обьякта: PUBLIC, STATIC, ENUM, STRUCT, Java_class
        uint8_t llt : 3;
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

    /// Объект который подчинаеться прастранству имён
    struct NS_Object {
        uint32_t namespace_id;
    };

    /// Значение
    struct Value_t : GC_Object {
        /// Тип значения: INT8 (1), INT16 (2), INT32 (3), INT64 (4), UINT8 (5), UINT16 (6), UINT32 (7), UINT64 (8), FLOAT (9), DOUBLE (10), CHAR (11), REFERENCE (12), OBJECT (13)
        uint8_t type : 4;
        /// Значение
        void* value;
    };

    /// Переменная
    struct Variable_t : Value_t, Nameble, NS_Object {
        /// Тип переменной: INT8 (1), INT16 (2), INT32 (3), INT64 (4), UINT8 (5), UINT16 (6), UINT32 (7), UINT64 (8), FLOAT (9), DOUBLE (10), CHAR (11), REFERENCE (12), OBJECT (13)
        uint8_t type : 4;
        /// Значение переменной
        void* value;
    };

    /// Лямбда
    struct Lambda_t : GC_Object {
        /// ID дескриптора
        SI_t descriptor;
        /// Размер байт-кода
        uint32_t code_size;
        /// Байт-код
        uint8_t* code;
    };

    /// Поле
    struct Field_t : LLT, Nameble {
        /// Значение
        Value_t* value;
    };

    /// Метод
    struct Method_t : Nameble, NS_Object {
        /// ID дескриптора
        SI_t descriptor;
        /// Размер байт-кода
        uint32_t code_size;
        /// Байт-код
        uint8_t* code;
    };

    /// Универсальная основа для Enum-а
    struct Enum_base : LLT, Nameble, NS_Object {
        /// Перечисления
        Variable_t** enums;
        /// Кол-во перечислений
        uint32_t enums_size : 8;
        //
        const uint8_t llt : 3 = 1;
    };

    struct Enum_8bit_t : Enum_base { uint8_t enums_size; };
    struct Enum_16bit_t : Enum_8bit_t { uint16_t enums_size; };
    struct Enum_32bit_t : Enum_16bit_t { uint32_t enums_size; };

    struct Struct_base : LLT, Nameble, NS_Object {
        /// Поля
        Field_t** fields;
        /// Кол-во полей
        uint32_t fields_size : 8;
        /// Предки (ID предков)
        CI_t* parents;
        /// Кол-во предков
        uint8_t parents_size : 5;
        //
        const uint8_t llt : 3 = 2;
    };

    struct Struct_8bit_t : Struct_base { uint8_t fields_size; };
    struct Struct_16bit_t : Struct_8bit_t { uint16_t fields_size; };
    struct Struct_32bit_t : Struct_16bit_t { uint32_t fields_size; };

    /// Универсальная основа для Class-а
    struct Class_base : LLT, Nameble, NS_Object {
        /// Массив полей
        Field_t** fields;
        /// Кол-во полей
        uint32_t fields_size : 8;
        /// Массив методов
        Method_t** methods;
        /// Кол-во методов
        uint32_t methods_size : 8;
        /// Предки (ID предков)
        CI_t* parents;
        /// Кол-во предков
        uint8_t parents_size : 5;
        //
        const uint8_t llt : 3 = 3;
    };

    struct Class_8bit_t : Class_base { uint8_t fields_size; uint8_t methods_size; };
    struct Class_16bit_t : Class_8bit_t { uint16_t fields_size; uint16_t methods_size; };
    struct Class_32bit_t : Class_16bit_t { uint32_t fields_size; uint32_t methods_size; };

    /// Абстрактная куча
    struct Heap {
        virtual CI_t addNewClass(Class_base* clazz) = NULL;
        virtual CI_t addClass(Class_base* clazz) = NULL;
        virtual void replaceClass(Class_base* clazz, CI_t id) = NULL;
        virtual void removeClass(Class_base* clazz) = NULL;
        virtual void removeClass(CI_t id) = NULL;
        virtual CI_t getClassId(Class_base* clazz) = NULL;
        virtual Class_base* getClass(CI_t id) = NULL;
        //
        virtual ::std::pair<Class_base**, size_t> getClassParents(Class_base* clazz) = NULL;
        virtual ::std::pair<Class_base**, size_t> getClassParents(CI_t clazz) = NULL;
    };

    /// Абстрактный загрузчик объектов
    struct ClassLoader {
        /* JVM */
        virtual Class_base* defineJVMClass(int8_t* bytes, size_t off, size_t len) = NULL;
        virtual Class_base* defineJVMClass(JP::Java_class_file* file) = NULL;
        /* .NET */
        // TODO: нужно реализовать
        /* KVM */
        virtual Class_base* defineKVMClass(int8_t* bytes, size_t off, size_t len) = NULL;
        virtual Struct_base* defineKVMStruct(int8_t* bytes, size_t off, size_t len) = NULL;
        virtual Enum_base* defineKVMEnum(int8_t* bytes, size_t off, size_t len) = NULL;
        virtual Method_t* defineKVMMethod(int8_t* bytes, size_t off, size_t len) = NULL;
        virtual Field_t* defineKVMField(int8_t* bytes, size_t off, size_t len) = NULL;
        /* Low Level Operations */
        // Создание класса
        virtual Class_base* createClass(Field_t** fields, uint8_t fields_size, Method_t** methods, uint8_t methods_size, CI_t* parents, uint8_t parents_size) = NULL;
        virtual Class_base* createClass(Field_t** fields, uint16_t fields_size, Method_t** methods, uint16_t methods_size, CI_t* parents, uint8_t parents_size) = NULL;
        virtual Class_base* createClass(Field_t** fields, uint32_t fields_size, Method_t** methods, uint32_t methods_size, CI_t* parents, uint8_t parents_size) = NULL;
        // Создание структуры
        virtual Struct_base* createStruct(Field_t** fields, uint8_t fields_size, CI_t* parents, uint8_t parents_size) = NULL;
        virtual Struct_base* createStruct(Field_t** fields, uint16_t fields_size, CI_t* parents, uint8_t parents_size) = NULL;
        virtual Struct_base* createStruct(Field_t** fields, uint32_t fields_size, CI_t* parents, uint8_t parents_size) = NULL;
        // Создание Enum-а
        virtual Enum_base* createEnum(Variable_t** enums, uint8_t enums_size) = NULL;
        virtual Enum_base* createEnum(Variable_t** enums, uint16_t enums_size) = NULL;
        virtual Enum_base* createEnum(Variable_t** enums, uint32_t enums_size) = NULL;
    };
}

#endif /* DMNKVM_KVMTYPES_HPP */