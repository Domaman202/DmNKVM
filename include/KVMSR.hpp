#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_SR_HPP
#define DMN_KVM_SR_HPP

#include "KVMConfig.hpp"
#include "SDmNL.hpp"

namespace DmN::KVM {
    template<typename T>
    class Stack : public SDL::List<T> {
        explicit Stack(SDL::Node<T>* start_node) : SDL::List<T>(start_node) {
        }

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

    class Resisters {
        explicit Resisters(size_t size) {
            this->register_storage = new void *[size];
            this->size = size;
        }

        ~Resisters() {
            delete[] this->register_storage;
        }

        /*!
         * Возвращает значение регистра по индексу
         * @param index индекс регистра
         * @return Значение регистра
         */
        void *&operator[](size_t index) const;

        /// Массив регистров
        void **register_storage;
        /// Размер
        size_t size;
    };
}

template<typename T>
inline void DmN::KVM::Stack<T>::push(T value) {
    this->add(value);
}

template<typename T>
inline void DmN::KVM::Stack<T>::pop() {
    this->removeLast();
}

template<typename T>
inline T DmN::KVM::Stack<T>::peekPop() {
    return this->removeLG();
}

template<typename T>
inline T DmN::KVM::Stack<T>::peek() {
    return this->getLast();
}

inline void*& DmN::KVM::Resisters::operator[](size_t index) const {
    return this->register_storage[index];
}

#endif /* DMN_KVM_SR_HPP */