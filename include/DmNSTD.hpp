#pragma once
#ifndef DMNSTD_HPP
#define DMNSTD_HPP

namespace DmN::std {
    template<typename T>
    struct Node {
        Node(T* value, Node<T>* next) {
            this->value = value;
            this->next = next;
        }

        T* value;
        Node<T>* next;
    };
}

#endif /* DMNSTD_HPP */