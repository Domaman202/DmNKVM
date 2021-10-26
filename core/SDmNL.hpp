#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_SDMNL_HPP
#define DMN_KVM_SDMNL_HPP

#include "KVMConfig.hpp"
#include <cstdint>
#include <cstdio>

namespace DmN::SDL {
    namespace Byte {
        typedef uint8_t u1;
        typedef uint16_t u2;
        typedef uint32_t u4;
        typedef uint64_t u8;
    }

    namespace Pairs {
        template<typename T1, typename T2>
        struct Tuple {
            Tuple(T1 v1, T2 v2) {
                value1 = v1;
                value2 = v2;
            }

            T1 value1;
            T2 value2;
        };

        template<typename T1, typename T2, typename T3>
        struct Triple {
            Triple(T1 v1, T2 v2, T3 v3) {
                value1 = v1;
                value2 = v2;
                value3 = v3;
            }

            T1 value1;
            T2 value2;
            T3 value3;
        };
    }

    template<typename T>
    struct DmNCollection {
        /*!
         * Добавляет новый элемент в коллекцию
         * @param obj
         */
        virtual void add(T obj) noexcept(false) = 0;
    };

    /// Нода
    template<typename T>
    struct Node {
        explicit Node(T value) {
            this->value = value;
            this->next = nullptr;
        }

        Node(T value, Node<T> *next) {
            this->value = value;
            this->next = next;
        }

        /// Значение ноды
        T value;
        /// Следующая нода
        Node<T> *next;
    };

    /// Лист
    template<typename T>
    struct List : public DmNCollection<T> {
        explicit List() {
            this->start_node = nullptr;
        }

        explicit List(Node<T> *start_node) {
            this->start_node = start_node;
        }

        /*!
         * Добавляет новый элемент в список
         * @param value элемент для добавления
         */
        void add(T value) override {
            if (this->start_node == nullptr) {
                this->start_node = new Node<T>(value);
                return;
            }

            Node<T>* last_node = this->start_node;
            while (last_node->next != nullptr)
                last_node = last_node->next;
            last_node->next = new Node<T>(value);
        }

        /*!
         * Добавляет новый элемент и возвращает его
         * @param value элемент для добавления
         * @return добавленный элемент
         */
        inline T addG(T value) {
            add(value);
            return value;
        }

        /*!
         * Устанавливает значение ноды, если ноды под нужным номером нет то добавляет её
         * @param index индекс ноды
         * @param value значение
         */
        void set(size_t index, T value) {
            Node<T>* last_node = this->start_node;
            while (index != 0) {
                if (last_node->next == nullptr)
                    last_node->next = new Node<T>();
                last_node = last_node->next;
                index--;
            }
            last_node->value = value;
        }

        /*!
         * Устанавливает значение ноды
         * @param index индекс ноды
         * @param value значение
         */
        inline void setUnsafe(size_t index, T value) {
            getNode(index)->value = value;
        }

        /*!
         * Возвращает ноду по ID
         * @param i ID ноды
         * @return нужная нам нода
         */
        Node<T> *getNode(size_t i) {
            Node<T>* last_node = this->start_node;
            while (i != 0) {
                last_node = last_node->next;
                i--;
            }
            return last_node;
        }

        /*!
         * Возвращает последнюю ноду
         * @return нужная нам нода
         */
        Node<T> *getLastNode() {
            if (this->start_node == nullptr)
                return nullptr;
            Node<T>* last_node = this->start_node;
            while (last_node->next != nullptr)
                last_node = last_node->next;
            return last_node;
        }

        /*!
         * Получает элемент по ID
         * @param i ID элемента
         * @return нужный нам элемент
         */
        inline T get(size_t i) {
            return this->getNode(i)->value;
        }

        /*!
         * Получает последний элемент
         * @return нужный нам элемент
         */
        T getLast() {
            Node<T>* last_node = this->start_node;
            while (last_node->next != nullptr)
                last_node = last_node->next;
            return last_node->value;
        }

        /*!
         * Убирает элемент из списка и возвращает его ноду
         * @param i ID элемента
         * @return нода элемента
         */
        Node<T> *removeGN(size_t i) {
            if (i == 0)
                return this->start_node;
            Node<T>* prev_node = this->getNode(i - 1);
            Node<T>* node_for_remove = prev_node->next;
            prev_node->next = node_for_remove->next;
            return node_for_remove;
        }

        /*!
         * Удаляет ноду элемента
         * @param i ID элемента
         */
        inline void remove(size_t i) {
            delete removeGN(i);
        }

        /*!
         * Удаляет элемент и возвращает его значение
         * @param i ID элемента
         * @return элемент
         */
        inline T removeG(size_t i) {
            Node<T>* node_for_remove = removeGN(i);
            T value = node_for_remove->value;
            delete node_for_remove;
            return value;
        }

        /*!
         * Убирает последний элемент из списка и возвращает его ноду
         * @return нода элемента
         */
        Node<T> *removeLGN() {
            Node<T>* pre_last_node = this->start_node;
            if (pre_last_node->next == nullptr) {
                this->start_node = nullptr;
                return pre_last_node;
            }
            while (pre_last_node->next->next != nullptr)
                pre_last_node = pre_last_node->next;
            Node<T>* node_for_remove = pre_last_node->next;
            pre_last_node->next = nullptr;
            return node_for_remove;
        }

        /*!
         * Удаляет последнюю ноду элемента
         */
        inline void removeLast() {
            delete removeLGN();
        }

        /*!
         * Удаляет последний элемент и возвращает его значение
         * @return элемент
         */
        inline T removeLG() {
            Node<T>* node_for_remove = removeLGN();
            T value = node_for_remove->value;
            delete node_for_remove;
            return value;
        }

        /*!
         * Чистит список
         */
        void clear() {
            while (this->start_node != nullptr) {
                Node<T>* next_node = this->start_node->next;
                delete this->start_node;
                this->start_node = next_node;
            }
        }

        /*!
         * Возвращает размер
         * @return размер списка
         */
        size_t size() {
            size_t size = 0;
            Node<T>* last_node = this->start_node;
            while (last_node != nullptr) {
                size++;
                last_node = last_node->next;
            }
            return size;
        }

        /**
         * Оператор доступа массивного типа
         * @param index индекс элемента
         * @return элемент
         */
        inline T& operator[] (size_t index) {
            return get(index);
        }

        inline void dealloc(Node<T>* prev_node, Node<T>* next_node) {
            delete prev_node->next;
            prev_node->next = next_node;
        }

        inline void dealloc(Node<T>* prev_node) {
            delete prev_node->next;
            prev_node->next = nullptr;
        }

        inline T deallocG(Node<T>* prev_node, Node<T>* next_node) {
            Node<T>* node_for_remove = prev_node->next;
            T value = node_for_remove->value;
            delete node_for_remove;
            prev_node->next = next_node;
            return value;
        }

        inline T deallocG(Node<T>* prev_node) {
            Node<T>* node_for_remove = prev_node->next;
            T value = node_for_remove;
            delete node_for_remove;
            prev_node->next = nullptr;
            return value;
        }

        /// Первая нода
        Node<T> *start_node;
    };
}

#endif /* DMN_KVM_SDMNL_HPP */