#pragma once
#ifndef DMNKVM_KVMCONSTRUCTORS_HPP
#define DMNKVM_KVMCONSTRUCTORS_HPP

#include <KVMTypes.hpp>
#include <cstdint>

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
    uint8_t try_collect(GC_Object* obj);

    /*!
     * Насильно собирает объект
     * \param obj - объект для сборки
     */
    void collect(GC_Object* obj);

    namespace ERROR {
        enum Collect_Result {
            SUCCESS = 0,
            OBJECT_NO_COLLECTABLE = 1,
            OBJECT_REFERENCE_NOT_NULL = 2
        };
    }
}

#endif /* DMNKVM_KVMCONSTRUCTORS_HPP */