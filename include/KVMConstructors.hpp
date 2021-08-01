#pragma once
#ifndef DMNKVM_KVMCONSTRUCTORS_HPP
#define DMNKVM_KVMCONSTRUCTORS_HPP

#include <KVMTypes.hpp>
#include <KVMError.hpp>

using namespace DmN::KVM::ERROR;

namespace DmN::KVM {
    /*!
     * (allocate static string storage)
     * Создаёт новое статическое хранилище строк
     * @param names - строки которые нужно добавить при создании
     * @return Новое хранилище строк
     */
    DMN_KVM_EXPORT SSS *allocSSS(char **names, size_t size);

    /*!
     * (allocate dynamic string storage)
     * Создаёт новое динамическое хранилище строк
     * @param names - строки которые нужно добавить при создании
     * @return Новое хранилище строк
     */
    DMN_KVM_EXPORT DSS *allocDSS(char **names, size_t size);

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