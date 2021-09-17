#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_SR_HPP
#define DMN_KVM_SR_HPP

#include "KVMConfig.hpp"
#include "SDmNL.hpp"

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

    DMN_KVM_E struct Resisters {
        explicit Resisters(size_t size) {
            this->regStorage = new void*[size];
            this->size = size;
        }

        ~Resisters() {
            delete[] this->regStorage;
        }

        /*!
         * Возвращает значение регистра по индексу
         * @param index индекс регистра
         * @return Значение регистра
         */
        void*& operator[](size_t index);

        /// Массив регистров
        void** regStorage;
        /// Размер
        size_t size;
    };
}

#endif /* DMN_KVM_SR_HPP */