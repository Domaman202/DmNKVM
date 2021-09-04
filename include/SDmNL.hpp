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

        DMN_KVM_EF u1 u1Read(FILE* file);
        DMN_KVM_EF u2 u2Read(FILE* file);
        DMN_KVM_EF u4 u4Read(FILE* file);
        DMN_KVM_EF u8 u8Read(FILE* file);
    }

    /// Нода
    template<typename T>
    DMN_KVM_E struct Node {
        Node(T value) {
            this->value = value;
        }

        Node(T value, Node<T>* next) {
            this->value = value;
            this->next = next;
        }

        /// Значение ноды
        T value;
        /// Следующая нода
        Node<T>* next;
    };

    /// Лист
    template<typename T>
    DMN_KVM_E struct List {
        explicit List(Node<T>* start_node) {
            this->start_node = start_node;
        }

        /*!
         * Добавляет новый элемент в список
         * @param value элемент для добавления
         */
        void add(T value) {
            if (this->start_node == nullptr) {
                this->start_node = new Node<T>(value);
                return;
            }

            Node<T>* last_node;
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
         * Возвращает ноду по ID
         * @param i ID ноды
         * @return нужная нам нода
         */
        Node<T>* getNode(size_t i) {
            Node<T>* last_node = this->start_node;
            while (i != 0) {
                last_node = last_node->next;
                i--;
            }
            return last_node;
        }

        /*!
         * Получает элемент по ID
         * @param i ID элемента
         * @return нужный нам элемент
         */
        T get(size_t i) {
            return this->getNode(i)->value;
        }

        /*!
         * Убирает элемент из списка и возвращает его ноду
         * @param i ID элемента
         * @return нода элемента
         */
        Node<T>* removeGN(size_t i) {
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
            return removeGN(i)->value;
        }

        /// Первая нода
        Node<T>* start_node;
    };

    DMN_KVM_EF unsigned int trans_two_byte(const unsigned char* bytes);
    DMN_KVM_EF unsigned int trans_three_byte(const unsigned char* bytes);
    DMN_KVM_EF unsigned int trans_six_bytes(const unsigned char* bytes);
    DMN_KVM_EF wchar_t trans_two_bytes_wchar(uint8_t byte1, uint8_t byte2);
    DMN_KVM_EF wchar_t trans_three_bytes_wchar(uint8_t byte1, uint8_t byte2, uint8_t byte3);
    DMN_KVM_EF wchar_t trans_six_bytes_wchar(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5, uint8_t byte6);
    DMN_KVM_EF int get_utf_8_width(unsigned char byte);
}

#endif /* DMN_KVM_SDMNL_HPP */