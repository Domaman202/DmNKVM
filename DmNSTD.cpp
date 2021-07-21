#include "DmNSTD.hpp"

namespace DmN::std {
    template<typename T>
    struct Node {
        T* value;
        Node<T>* next;
    };
}