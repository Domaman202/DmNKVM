#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_SDMNL_HPP
#define DMN_KVM_SDMNL_HPP

#include <KVMConfig.hpp>
#include <cstdint>
#include <cstdio>

namespace DmN::SDL {
    namespace Byte {
        typedef uint8_t u1;
        typedef uint16_t u2;
        typedef uint32_t u4;
        typedef uint64_t u8;

        DMN_KVM_EF u1 u1Read(FILE *file);

        DMN_KVM_EF u2 u2Read(FILE *file);

        DMN_KVM_EF u4 u4Read(FILE *file);

        DMN_KVM_EF u8 u8Read(FILE *file);
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

    /// Нода
    template<typename T>
    DMN_KVM_E
    struct Node {
        explicit Node(T value) {
            this->value = value;
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
    DMN_KVM_E
    struct List {
        explicit List(Node<T> *start_node) {
            this->start_node = start_node;
        }

        /*!
         * Добавляет новый элемент в список
         * @param value элемент для добавления
         */
        void add(T value);

        /*!
         * Добавляет новый элемент и возвращает его
         * @param value элемент для добавления
         * @return добавленный элемент
         */
        T addG(T value);

        /*!
         * Возвращает ноду по ID
         * @param i ID ноды
         * @return нужная нам нода
         */
        Node<T> *getNode(size_t i);

        /*!
         * Возвращает последнюю ноду
         * @return нужная нам нода
         */
        Node<T> *getLastNode();

        /*!
         * Получает элемент по ID
         * @param i ID элемента
         * @return нужный нам элемент
         */
        T get(size_t i);

        /*!
         * Получает последний элемент
         * @return нужный нам элемент
         */
        T getLast();

        /*!
         * Убирает элемент из списка и возвращает его ноду
         * @param i ID элемента
         * @return нода элемента
         */
        Node<T> *removeGN(size_t i);

        /*!
         * Удаляет ноду элемента
         * @param i ID элемента
         */
        void remove(size_t i);

        /*!
         * Удаляет элемент и возвращает его значение
         * @param i ID элемента
         * @return элемент
         */
        T removeG(size_t i);

        /*!
         * Убирает последний элемент из списка и возвращает его ноду
         * @return нода элемента
         */
        Node<T> *removeLGN();

        /*!
         * Удаляет последнюю ноду элемента
         */
        void removeLast();

        /*!
         * Удаляет последний элемент и возвращает его значение
         * @return элемент
         */
        T removeLG();

        /// Первая нода
        Node<T> *start_node;
    };
}

#endif /* DMN_KVM_SDMNL_HPP */