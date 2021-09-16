#include <SDmNL.hpp>

namespace DmN::SDL {
    namespace Byte {
        inline u1 u1Read(FILE* file) {
            return getc(file);
        }

        inline u2 u2Read(FILE* file) {
            return (u1Read(file) << 4) | u1Read(file);
        }

        inline u4 u4Read(FILE* file) {
            return (u2Read(file) << 8 | u2Read(file));
        }

        inline u8 u8Read(FILE* file) {
            return (u4Read(file) << 16 | u4Read(file));
        }
    }

    template<typename T>
    void List<T>::add(T value) {
        if (this->start_node == nullptr) {
            this->start_node = new Node<T>(value);
            return;
        }

        Node<T>* last_node;
        while (last_node->next != nullptr)
            last_node = last_node->next;
        last_node->next = new Node<T>(value);
    }

    template<typename T>
    inline T List<T>::addG(T value) {
        add(value);
        return value;
    }

    template<typename T>
    void List<T>::set(size_t index, T value) {
        Node<T>* last_node = this->start_node;
        while (index != 0) {
            if (last_node->next == nullptr)
                last_node->next = new Node<T>();
            last_node = last_node->next;
            index--;
        }
        last_node->value = value;
    }

    template<typename T>
    void List<T>::setUnsafe(size_t index, T value) {
        getNode(index)->value = value;
    }

    template<typename T>
    Node<T>* List<T>::getNode(size_t i) {
        Node<T>* last_node = this->start_node;
        while (i != 0) {
            last_node = last_node->next;
            i--;
        }
        return last_node;
    }

    template<typename T>
    Node<T>* List<T>::getLastNode() {
        Node<T> last_node = this->start_node;
        while (last_node->next != nullptr)
            last_node = last_node->next;
        return last_node.value;
    }

    template<typename T>
    T List<T>::get(size_t i) {
        return this->getNode(i)->value;
    }

    template<typename T>
    T List<T>::getLast() {
        Node<T> last_node = this->start_node;
        while (last_node->next != nullptr)
            last_node = last_node->next;
        return last_node.value;
    }

    template<typename T>
    Node<T>* List<T>::removeGN(size_t i) {
        if (i == 0) {
            Node<T>* node_for_remove = this->start_node;
            this->start_node = nullptr;
            return node_for_remove;
        }

        Node<T>* prev_node = this->getNode(i - 1);
        Node<T>* node_for_remove = prev_node->next;
        prev_node->next = node_for_remove->next;
        return node_for_remove;
    }

    template<typename T>
    inline void List<T>::remove(size_t i) {
        delete removeGN(i);
    }

    template<typename T>
    inline T List<T>::removeG(size_t i) {
        return removeGN(i)->value;
    }

    template<typename T>
    Node<T>* List<T>::removeLGN() {
        Node<T>* pre_last_node = this->start_node;
        while (pre_last_node->next->next != nullptr)
            pre_last_node = pre_last_node->next;
        Node<T>* node_for_remove = pre_last_node->next;
        pre_last_node->next = nullptr;
        return node_for_remove;
    }

    template<typename T>
    inline void List<T>::removeLast() {
        delete removeLGN();
    }

    template<typename T>
    inline T List<T>::removeLG() {
        return removeLGN()->value;
    }

    template<typename T>
    inline T& List<T>::operator[] (size_t index) {
        return get(index);
    }
}