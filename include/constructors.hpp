#pragma once
#ifndef DMNKVM_CONSTRUCTORS_HPP
#define DMNKVM_CONSTRUCTORS_HPP

#include <types.hpp>
#include <cstdint>

namespace DmN::KVM {
    /*!
     * Пытаеться собрать объект
     * \param obj - объект для сборки
    */
    uint8_t try_collect(GC_Object* obj);

    /*!
     * Насильно собирает объект
     * \param obj - объект для сборки
     */
    void collect(GC_Object* obj);
}

#endif /* DMNKVM_CONSTRUCTORS_HPP */