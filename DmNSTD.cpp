#include "DmNSTD.hpp"

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