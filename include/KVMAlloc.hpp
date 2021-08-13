#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_ALLOC_HPP
#define DMN_KVM_ALLOC_HPP

#include <KVMESC.hpp>

namespace DmN::KVM {
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
    ClassBase* allocateClass8BS(SI_t name, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);

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
    ClassBase* allocateNSClass8BS(SI_t name, NSI_t ns, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);

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
    ClassBase* allocateClass8BH(SI_t name, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);

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
    ClassBase* allocateNSClass8BH(SI_t name, uint8_t modifier, NSI_t ns, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);

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
    ClassBase* allocateClass16BS(SI_t name, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);

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
    ClassBase* allocateNSClass16BS(SI_t name, NSI_t ns, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);

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
    ClassBase* allocateClass16BH(SI_t name, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);

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
    ClassBase* allocateNSClass16BH(SI_t name, NSI_t ns, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);

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
    ClassBase* allocateClass64BS(SI_t name, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);

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
    ClassBase* allocateNSClass64BS(SI_t name, uint8_t modifier, NSI_t ns, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);

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
    ClassBase* allocateClass64BH(SI_t name, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);

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
    ClassBase* allocateNSClass64BH(SI_t name, NSI_t ns, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);
}

#endif /* DMN_KVM_ALLOC_HPP */