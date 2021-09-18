#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_ALLOC_HPP
#define DMN_KVM_ALLOC_HPP

#include "KVMESC.hpp"

namespace DmN::KVM::Alloc {
    /*!
     * (allocate static string storage)
     * Создаёт новое статическое хранилище строк
     * @param names строки которые нужно добавить при создании
     * @return Новое хранилище строк
     */
    SS *allocSSS(char **names, size_t size);

    /*!
     * (allocate dynamic string storage)
     * Создаёт новое динамическое хранилище строк
     * @param names строки которые нужно добавить при создании
     * @return Новое хранилище строк
     */
    SS *allocDSS(char **names, size_t size);

    /*!
     * Создаёт 8и битный класс на стеке
     * @param name Имя класса
     * @param fields Поля класса
     * @param fieldsCount Кол-во полей класса
     * @param methods Методы класса
     * @param methodsCount Кол-во методов класса
     * @param parents Предки класса
     * @param parentsCount Кол-во предков класса
     * @return Созданный класс или nullptr в случае ошибки (создания/выделения памяти под класс)
     */
    ClassBase *allocateClass8BS(SI_t
                                name,
                                uint8_t modifier, Field_t
                                **fields,
                                uint32_t fieldsCount, Method_t
                                **methods,
                                uint32_t methodsCount, CI_t
                                *parents,
                                uint8_t parentsCount
    );

    /*!
     * Создаёт 8и битный класс на стеке
     * @param name Имя класса
     * @param ns Пространство имён в котором валяется класс
     * @param fields Поля класса
     * @param fieldsCount Кол-во полей класса
     * @param methods Методы класса
     * @param methodsCount Кол-во методов класса
     * @param parents Предки класса
     * @param parentsCount Кол-во предков класса
     * @return Созданный класс или nullptr в случае ошибки (создания/выделения памяти под класс)
     */
    ClassBase *allocateNSClass8BS(SI_t
                                  name,
                                  NSI_t ns, uint8_t
                                  modifier,
                                  Field_t **fields, uint32_t
                                  fieldsCount,
                                  Method_t **methods, uint32_t
                                  methodsCount,
                                  CI_t *parents, uint8_t
                                  parentsCount);

    /*!
     * Создаёт 8и битный класс в куче
     * @param name Имя класса
     * @param fields Поля класса
     * @param fieldsCount Кол-во полей класса
     * @param methods Методы класса
     * @param methodsCount Кол-во методов класса
     * @param parents Предки класса
     * @param parentsCount Кол-во предков класса
     * @return Созданный класс или nullptr в случае ошибки (создания/выделения памяти под класс)
     */
    ClassBase *allocateClass8BH(SI_t
                                name,
                                uint8_t modifier, Field_t
                                **fields,
                                uint32_t fieldsCount, Method_t
                                **methods,
                                uint32_t methodsCount, CI_t
                                *parents,
                                uint8_t parentsCount
    );

    /*!
     * Создаёт 8и битный класс в куче
     * @param name Имя класса
     * @param ns Пространство имён в котором валяется класс
     * @param fields Поля класса
     * @param fieldsCount Кол-во полей класса
     * @param methods Методы класса
     * @param methodsCount Кол-во методов класса
     * @param parents Предки класса
     * @param parentsCount Кол-во предков класса
     * @return Созданный класс или nullptr в случае ошибки (создания/выделения памяти под класс)
     */
    ClassBase *allocateNSClass8BH(SI_t
                                  name,
                                  uint8_t modifier, NSI_t
                                  ns,
                                  Field_t **fields, uint32_t
                                  fieldsCount,
                                  Method_t **methods, uint32_t
                                  methodsCount,
                                  CI_t *parents, uint8_t
                                  parentsCount);

    /*!
     * Создаёт 16и битный класс на стеке
     * @param name Имя класса
     * @param fields Поля класса
     * @param fieldsCount Кол-во полей класса
     * @param methods Методы класса
     * @param methodsCount Кол-во методов класса
     * @param parents Предки класса
     * @param parentsCount Кол-во предков класса
     * @return Созданный класс или nullptr в случае ошибки (создания/выделения памяти под класс)
     */
    ClassBase *allocateClass16BS(SI_t
                                 name,
                                 uint8_t modifier, Field_t
                                 **fields,
                                 uint32_t fieldsCount, Method_t
                                 **methods,
                                 uint32_t methodsCount, CI_t
                                 *parents,
                                 uint8_t parentsCount
    );

    /*!
     * Создаёт 16и битный класс на стеке
     * @param name Имя класса
     * @param ns Пространство имён в котором валяется класс
     * @param fields Поля класса
     * @param fieldsCount Кол-во полей класса
     * @param methods Методы класса
     * @param methodsCount Кол-во методов класса
     * @param parents Предки класса
     * @param parentsCount Кол-во предков класса
     * @return Созданный класс или nullptr в случае ошибки (создания/выделения памяти под класс)
     */
    ClassBase *allocateNSClass16BS(SI_t
                                   name,
                                   NSI_t ns, uint8_t
                                   modifier,
                                   Field_t **fields, uint32_t
                                   fieldsCount,
                                   Method_t **methods, uint32_t
                                   methodsCount,
                                   CI_t *parents, uint8_t
                                   parentsCount);

    /*!
     * Создаёт 16и битный класс в куче
     * @param name Имя класса
     * @param fields Поля класса
     * @param fieldsCount Кол-во полей класса
     * @param methods Методы класса
     * @param methodsCount Кол-во методов класса
     * @param parents Предки класса
     * @param parentsCount Кол-во предков класса
     * @return Созданный класс или nullptr в случае ошибки (создания/выделения памяти под класс)
     */
    ClassBase *allocateClass16BH(SI_t
                                 name,
                                 uint8_t modifier, Field_t
                                 **fields,
                                 uint32_t fieldsCount, Method_t
                                 **methods,
                                 uint32_t methodsCount, CI_t
                                 *parents,
                                 uint8_t parentsCount
    );

    /*!
     * Создаёт 16ми битный класс в куче
     * @param name Имя класса
     * @param ns Пространство имён в котором валяется класс
     * @param fields Поля класса
     * @param fieldsCount Кол-во полей класса
     * @param methods Методы класса
     * @param methodsCount Кол-во методов класса
     * @param parents Предки класса
     * @param parentsCount Кол-во предков класса
     * @return Созданный класс или nullptr в случае ошибки (создания/выделения памяти под класс)
     */
    ClassBase *allocateNSClass16BH(SI_t
                                   name,
                                   NSI_t ns, uint8_t
                                   modifier,
                                   Field_t **fields, uint32_t
                                   fieldsCount,
                                   Method_t **methods, uint32_t
                                   methodsCount,
                                   CI_t *parents, uint8_t
                                   parentsCount);

    /*!
     * Создаёт 64х битный класс на стеке
     * @param name Имя класса
     * @param fields Поля класса
     * @param fieldsCount Кол-во полей класса
     * @param methods Методы класса
     * @param methodsCount Кол-во методов класса
     * @param parents Предки класса
     * @param parentsCount Кол-во предков класса
     * @return Созданный класс или nullptr в случае ошибки (создания/выделения памяти под класс)
     */
    ClassBase *allocateClass64BS(SI_t
                                 name,
                                 uint8_t modifier, Field_t
                                 **fields,
                                 uint32_t fieldsCount, Method_t
                                 **methods,
                                 uint32_t methodsCount, CI_t
                                 *parents,
                                 uint8_t parentsCount
    );

    /*!
     * Создаёт 64х битный класс на стеке
     * @param name Имя класса
     * @param ns Пространство имён в котором валяется класс
     * @param fields Поля класса
     * @param fieldsCount Кол-во полей класса
     * @param methods Методы класса
     * @param methodsCount Кол-во методов класса
     * @param parents Предки класса
     * @param parentsCount Кол-во предков класса
     * @return Созданный класс или nullptr в случае ошибки (создания/выделения памяти под класс)
     */
    ClassBase *allocateNSClass64BS(SI_t
                                   name,
                                   uint8_t modifier, NSI_t
                                   ns,
                                   Field_t **fields, uint32_t
                                   fieldsCount,
                                   Method_t **methods, uint32_t
                                   methodsCount,
                                   CI_t *parents, uint8_t
                                   parentsCount);

    /*!
     * Создаёт 64х битный класс в куче
     * @param name Имя класса
     * @param fields Поля класса
     * @param fieldsCount Кол-во полей класса
     * @param methods Методы класса
     * @param methodsCount Кол-во методов класса
     * @param parents Предки класса
     * @param parentsCount Кол-во предков класса
     * @return Созданный класс или nullptr в случае ошибки (создания/выделения памяти под класс)
     */
    ClassBase *allocateClass64BH(SI_t
                                 name,
                                 uint8_t modifier, Field_t
                                 **fields,
                                 uint32_t fieldsCount, Method_t
                                 **methods,
                                 uint32_t methodsCount, CI_t
                                 *parents,
                                 uint8_t parentsCount
    );

    /*!
     * Создаёт 64х битный класс в куче
     * @param name Имя класса
     * @param ns Пространство имён в котором валяется класс
     * @param fields Поля класса
     * @param fieldsCount Кол-во полей класса
     * @param methods Методы класса
     * @param methodsCount Кол-во методов класса
     * @param parents Предки класса
     * @param parentsCount Кол-во предков класса
     * @return Созданный класс или nullptr в случае ошибки (создания/выделения памяти под класс)
     */
    ClassBase *allocateNSClass64BH(SI_t
                                   name,
                                   NSI_t ns, uint8_t
                                   modifier,
                                   Field_t **fields, uint32_t
                                   fieldsCount,
                                   Method_t **methods, uint32_t
                                   methodsCount,
                                   CI_t *parents, uint8_t
                                   parentsCount);

    ClassBase *allocClass8B(SI_t name, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods,
                            uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) {
        return new Class_8bit_t(name, modifier, fields, fieldsCount, methods, methodsCount, parents, parentsCount);
    }

    ClassBase *allocClass16B(SI_t name, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods,
                             uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) {
        return new Class_16bit_t(name, modifier, fields, fieldsCount, methods, methodsCount, parents, parentsCount);
    }

    ClassBase *allocClass32B(SI_t name, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods,
                             uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) {
        return new Class_32bit_t(name, modifier, fields, fieldsCount, methods, methodsCount, parents, parentsCount);
    }

    NSClassBase *
    allocNSClass8B(SI_t name, NSI_t ns, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods,
                   uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) {
        return new NSClass_8bit_t(name, ns, modifier, fields, fieldsCount, methods, methodsCount, parents,
                                  parentsCount);
    }

    NSClassBase *
    allocNSClass16B(SI_t name, NSI_t ns, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods,
                    uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) {
        return new NSClass_16bit_t(name, ns, modifier, fields, fieldsCount, methods, methodsCount, parents,
                                   parentsCount);
    }

    NSClassBase *
    allocNSClass32B(SI_t name, NSI_t ns, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods,
                    uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) {
        return new NSClass_32bit_t(name, ns, modifier, fields, fieldsCount, methods, methodsCount, parents,
                                   parentsCount);
    }

    SS *allocSSS(char **names, size_t size) {
        // Создаём хранилище строк
        SSS *storage = new SSS(size);
        // Пихаем имена
        while (size != 0)
            storage->addNew(names[--size]);
        // Возвращаем хранилище строк
        return storage;
    }

    SS *allocDSS(char **names, size_t size) {
        // Создаём хранилище строк
        auto *storage = new DSS;
        // Пихаем имена
        while (size != 0)
            storage->addNew(names[--size]);
        // Возвращаем хранилище строк
        return storage;
    }

    CR tryCollect(GCObject *obj) {
        // Проверяем можно ли собрать объект
        if (obj->isCollectable) {
            // Если объект собирается проверяем кол-во ссылок
            if (obj->references == 0) {
                // Высвобождаем память
                delete obj;
                // Выводим код успешного выполнения
                return (CR) Error::SUCCESS;
            }
            // Иначе выводим код ошибки
            return Error::OBJECT_REFERENCE_NOT_NULL;
        }
        // Иначе выводим код ошибки
        return Error::OBJECT_NO_COLLECTABLE;
    }

    inline void collect(GCObject *obj) {
        // Высвобождаем память
        delete obj;
    }
}

#endif /* DMN_KVM_ALLOC_HPP */