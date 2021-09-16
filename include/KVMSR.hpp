#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_SR_HPP
#define DMN_KVM_SR_HPP

#include "KVMConfig.hpp"
#include "SDmNL.hpp"
#include <type_traits>
#include <concepts>

namespace DmN::KVM {
    template<typename T>
    DMN_KVM_E struct Stack : public SDL::List<T> {
        /*!
         * Помещает элемент в верх стек
         * @param value элемент для помещения в стек
         */
        void push(T value);

        /*!
         * Удаляет элемент сверху стека
         */
        void pop();

        /*!
         * Удаляет элемент с вершины стека и возвращает его
         * @return Удалённый элемент
         */
        [[nodiscard]] T peekPop();

        /*!
         * Возвращает элемент с вершины стека
         * @return Элемент с вершины стека
         */
        [[nodiscard]] T peek();
    };

    template <typename T>
    concept RegisterConcept =
            requires(T obj, size_t index) {
                { obj[index] } -> std::convertible_to<void*>;
            };

    DMN_KVM_E struct Resisters {
        // TODO:
    };
}

#endif /* DMN_KVM_SR_HPP */