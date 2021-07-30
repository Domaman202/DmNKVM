#pragma once
#ifndef DMNKVM_KVMCONSTRUCTORS_HPP
#define DMNKVM_KVMCONSTRUCTORS_HPP

#include <KVMConfig.hpp>
#include <KVMTypes.hpp>
#include <KVMError.hpp>

#include <cstdint>

using namespace DmN::KVM::ERROR;

namespace DmN::KVM {
    /*!
     * (allocate dynamic string storage)
     * Создаёт новое динамическое хранилище строк
     * @param names - строки которые нужно добавить при создании
     * @return Новое хранилище строк
     */
    export DSS* allocDSS(char **names, size_t size);

    /*!
     * Пытаеться собрать объект
     * \param obj - объект для сборки
     * \return возвращает значение из DmN::KVM::ERROR::CR
    */
    export CR tryCollect(GC_Object* obj);

    /*!
     * Насильно собирает объект
     * \param obj - объект для сборки
     */
    export inline void collect(GC_Object* obj);
}

#endif /* DMNKVM_KVMCONSTRUCTORS_HPP */