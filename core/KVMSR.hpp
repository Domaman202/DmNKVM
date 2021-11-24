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
    public:
        explicit Stack(SDL::Node<T> *start_node) : SDL::List<T>(start_node) {
        }

        /*!
         * Помещает элемент в верх стек
         * @param value элемент для помещения в стек
         */
        void push(T value) {
            this->add(value);
        }

        /*!
         * Удаляет элемент сверху стека
         */
        void pop() {
            this->removeLast();
        }

        /*!
         * Удаляет элемент с вершины стека и возвращает его
         * @return Удалённый элемент
         */
        [[nodiscard]] T peekPop() {
            return this->removeLG();
        }

        /*!
         * Возвращает элемент с вершины стека
         * @return Элемент с вершины стека
         */
        [[nodiscard]] T peek() {
            return this->getLast();
        }
    };

    class Resisters {
    public:
        explicit Resisters(size_t size) {
            this->rs = new void *[size];
            this->size = size;
        }

        ~Resisters() {
            delete[] this->rs;
        }

        /*!
         * Возвращает значение регистра по индексу
         * @param index индекс регистра
         * @return Значение регистра
         */
        inline void *&operator[](size_t index) {
            return this->rs[index];
        }

        /// Массив регистров
        void **rs;
        /// Размер
        size_t size;
    };
}

#endif /* DMN_KVM_SR_HPP */