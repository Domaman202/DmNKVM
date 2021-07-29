#pragma once
#ifndef DMNKVM_KVMCONSTRUCTORS_HPP
#define DMNKVM_KVMCONSTRUCTORS_HPP

#include <KVMTypes.hpp>
#include <KVMError.hpp>

#include <cstdint>

using namespace DmN::KVM::ERROR;

namespace DmN::KVM {
    /*!
     * Создаёт новое хранилище строк
     * @param names - строки которые нужно добавить при создании
     * @return Новое хранилище строк
     */
    DynamicStringStorage* allocate_DynamicStringStorage(char* names[], size_t size);

    /*!
     * Пытаеться собрать объект
     * \param obj - объект для сборки
     * \return возвращает значение из DmN::KVM::ERROR::Collect_Result
    */
    Collect_Result try_collect(GC_Object* obj);

    /*!
     * Насильно собирает объект
     * \param obj - объект для сборки
     */
    inline void collect(GC_Object* obj);
}

#endif /* DMNKVM_KVMCONSTRUCTORS_HPP */