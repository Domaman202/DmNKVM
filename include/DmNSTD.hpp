#pragma once
#ifndef DMNKVM_DMNSTD_HPP
#define DMNKVM_DMNSTD_HPP

namespace DmN::std {
    /// Нода
    template<typename T>
    struct Node {
        Node(T* value, Node<T>* next) {
            this->value = value;
            this->next = next;
        }

        /// Значение ноды
        T* value;
        /// Следующая нода
        Node<T>* next;
    };
}

#endif /* DMNKVM_DMNSTD_HPP */