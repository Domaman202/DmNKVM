#pragma once
#ifndef DMNKVM_KVMCONSTRUCTORS_HPP
#define DMNKVM_KVMCONSTRUCTORS_HPP

#include <KVMTypes.hpp>
#include <KVMError.hpp>
#include <KVMESC.hpp>

using namespace DmN::KVM::ERROR;

namespace DmN::KVM {
    /*!
     * Создаёт новый 8-битный класс
     */
    DMN_KVM_EXPORT ClassBase* allocClass8B(SI_t name, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);

    /*!
    * Создаёт новый 16-битный класс
    */
    DMN_KVM_EXPORT ClassBase* allocClass16B(SI_t name, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);

    /*!
     * Создаёт новый 32-битный класс
     */
    DMN_KVM_EXPORT ClassBase* allocClass32B(SI_t name, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);

    /*!
     * Создаёт новый 8-битный класс
     */
    DMN_KVM_EXPORT NSClassBase* allocNSClass8B(SI_t name, NSI_t ns, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);

    /*!
    * Создаёт новый 16-битный класс
    */
    DMN_KVM_EXPORT NSClassBase* allocNSClass16B(SI_t name, NSI_t ns, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);

    /*!
     * Создаёт новый 32-битный класс
     */
    DMN_KVM_EXPORT NSClassBase* allocNSClass32B(SI_t name, NSI_t ns, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount);

    /*!
     * (allocate static string storage)
     * Создаёт новое статическое хранилище строк
     * @param names - строки которые нужно добавить при создании
     * @return Новое хранилище строк
     */
    DMN_KVM_EXPORT SS *allocSSS(char **names, size_t size);

    /*!
     * (allocate dynamic string storage)
     * Создаёт новое динамическое хранилище строк
     * @param names - строки которые нужно добавить при создании
     * @return Новое хранилище строк
     */
    DMN_KVM_EXPORT SS *allocDSS(char **names, size_t size);

    /*!
     * Пытаеться собрать объект
     * \param obj - объект для сборки
     * \return возвращает значение из DmN::KVM::ERROR::CR
    */
    DMN_KVM_EXPORT CR tryCollect(GCObject *obj);

    /*!
     * Насильно собирает объект
     * \param obj - объект для сборки
     */
    DMN_KVM_EXPORT inline void collect(GCObject *obj);
}

#endif /* DMNKVM_KVMCONSTRUCTORS_HPP */