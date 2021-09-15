#include <KVMSR.hpp>

namespace DmN::KVM {
    template<typename T>
    inline void Stack<T>::push(T value) {
        this->add(value);
    }

    template<typename T>
    inline void Stack<T>::pop() {
        this->removeGNLast();
    }

    template<typename T>
    inline T Stack<T>::peekPop() {
        return this->removeGLast();
    }

    template<typename T>
    inline T Stack<T>::peek() {
        return this->getLast();
    }
}