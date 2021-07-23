#include "DmNKVM.hpp"
#include "DmNSTD.cpp"
#include <cstdint>
#include <cstring>
#include <malloc.h>

using namespace DmN::std;

namespace DmN::KVM {
    /// Хрень которая содержит имя
    struct Nameble {
        uint32_t name_id;
    };
    /// Name and ID
    struct NaI : Node<char> {
        NaI(char* name, uint32_t id, NaI* next) : Node<char>(name, next) {
            this->id = id;
        }

        uint32_t id;
        NaI* next;
    };
    /// Хренилище имён
    class NameStorage {
        NaI* start_node;

        uint32_t addNewName(char* name) {
            NaI* last_node = start_node;
            while (last_node->next != nullptr)
                last_node = last_node->next;
            last_node->next = new NaI(name, last_node->id++, nullptr);
            return last_node->next->id;
        }

        uint32_t addName(char* name) {
            NaI* last_node = start_node;
            while (last_node->next != nullptr) {
                if (strcmp(last_node->value, name) == 0)
                    return last_node->id;
                last_node = last_node->next;
            }
            if (strcmp(last_node->value, name) == 0)
                return last_node->id;
            last_node->next = new NaI(name, last_node->id++, nullptr);
            return last_node->next->id;
        }

        /// Получает имя по ID
        char* getName(uint32_t id) {
            // Перебираем ноды
            NaI* last_node = start_node;
            for (; id > 0; --id)
                last_node = last_node->next;
            // Возвращаем имя полученое по ID
            return last_node->value;
        }

        /// Получаем ID по имени
        uint32_t getId(char* name) {
            // Перебираем ноды
            NaI* last_node = start_node;
            while (last_node != nullptr) {
                // Сравниваем имена
                if (strcmp(last_node->value, name) == 0)
                    // Если имена правильны то возвращаем нужный ID
                    return last_node->id;
                // Перебираем ноды дальше
                last_node = last_node->next;
            }
            // Если нихрена не нашли то возвращаем 0
            return 0;
        }

        /// Удаляем имя из списка по ID и возвращает само имя
        char* remove(uint32_t id) {
            // Перебираем ноды
            NaI* last_node = start_node;
            for (; id > 0; id--)
                last_node = last_node->next;
            // Получаем ноду имени для удаления
            NaI* node_for_remove = last_node->next;
            // Получаем имя
            char* name = node_for_remove->value;
            // Выпиливаем ноду из списка
            last_node->next = node_for_remove->next;
            // Высвобождаем память
            free(node_for_remove->value);
            free(node_for_remove);
            // Возвращаем имя
            return name;
        }

        /// Удаляет имя из списка и возвращает ID
        uint32_t remove(char* name) {
            // Перебираем ноды
            NaI* last_node = start_node;
            while (last_node != nullptr) {
                if (strcmp(last_node->next->value, name) == 0) {
                    // Получаем ноду имени для удаления
                    NaI* node_for_remove = last_node->next;
                    // Получаем ID
                    uint32_t i = node_for_remove->id;
                    // Выпиливаем ноду из списка
                    last_node->next = node_for_remove->next;
                    // Высвобождаем память
                    free(node_for_remove->value);
                    free(node_for_remove);
                    // Возвращаем ID
                    return i;
                }
                last_node = last_node->next;
            }
            return 0;
        }
    };
}