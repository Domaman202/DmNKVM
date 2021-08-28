#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_CONSTRUCTORS_HPP
#define DMN_KVM_CONSTRUCTORS_HPP

#include "KVMError.hpp"
#include "KVMESC.hpp"

using namespace DmN::KVM::ERROR;

namespace DmN::KVM {
    /*!
     * (allocate static string storage)
     * Создаёт новое статическое хранилище строк
     * @param names строки которые нужно добавить при создании
     * @return Новое хранилище строк
     */
    DMN_KVM_EF SS* allocSSS(char **names, size_t size);

    /*!
     * (allocate dynamic string storage)
     * Создаёт новое динамическое хранилище строк
     * @param names строки которые нужно добавить при создании
     * @return Новое хранилище строк
     */
    DMN_KVM_EF SS* allocDSS(char **names, size_t size);

    /*!
     * Пытается собрать объект
     * @param obj объект для сборки
     * @return возвращает значение из DmN::KVM::ERROR::CR
    */
    DMN_KVM_EF CR tryCollect(GCObject *obj);

    /*!
     * Насильно собирает объект
     * @param obj объект для сборки
     */
    DMN_KVM_EF inline void collect(GCObject *obj);
}

#endif /* DMN_KVM_CONSTRUCTORS_HPP */