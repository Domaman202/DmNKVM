#include <KVMTypes.hpp>
#include <DmNSTD.hpp>
#include <cstdint>
#include <cstring>
#include <malloc.h>

using namespace DmN::std;

namespace DmN::KVM {
    uint32_t StringStorage::addNewName(char* name) {
        // Перебираем ноды
        SaI* last_node = start_node;
        while (last_node->next != nullptr)
            last_node = last_node->next;
        // Пихаем новую ноду с новой строкой
        last_node->next = new SaI(name, last_node->id++, nullptr);
        // Возвращаем ID новой строки
        return last_node->next->id;
    }

    uint32_t StringStorage::addName(char* name) {
        // Переменная для пустой ноды
        SaI* free_node = start_node;
        // Перебираем ноды
        SaI* last_node = start_node;
        while (last_node->next != nullptr) {
            // Проверяем на существование имени
            if (strcmp(last_node->value, name) == 0)
                // Возвращаем ID этого имени
                return last_node->id;
            // Перебираем ноды
            last_node = last_node->next;
            // Если нода пуста то сохраняем её
            if (free_node == start_node && last_node->value == nullptr)
                free_node = last_node;
        }
        // Проверяем на существование строки
        if (strcmp(last_node->value, name) == 0)
            // Возвращаем ID этой строки
            return last_node->id;
        // Пихаем новую ноду с новой строкой
        if (free_node == last_node) {
            // Если у нас нет свободной ноды то создаём новую и пихаем туда значение
            last_node->next = new SaI(name, last_node->id++, nullptr);
            // Возвращаем ID новой строки
            return last_node->next->id;
        }
        // Иначе пихаем значение в свободную ноду
        free_node->value = name;
        // Возвращаем ID новой строки
        return last_node->next->id;
    }

    char* StringStorage::getName(uint32_t id) {
        // Перебираем ноды
        SaI* last_node = start_node;
        for (; id > 0; --id)
            last_node = last_node->next;
        // Возвращаем строку полученную по ID
        return last_node->value;
    }

    uint32_t StringStorage::getId(char* name) {
        // Перебираем ноды
        SaI* last_node = start_node;
        while (last_node != nullptr) {
            // Сравниваем имена
            if (strcmp(last_node->value, name) == 0)
                // Если строки совпадают то возвращаем нужный ID
                return last_node->id;
            // Перебираем ноды дальше
            last_node = last_node->next;
        }
        // Если нихрена не нашли то возвращаем 0
        return 0;
    }

    char* StringStorage::free(uint32_t id) {
        // Перебираем ноды
        SaI* last_node = start_node;
        for (; id > 0; id--)
            last_node = last_node->next;
        // Получаем ноду строки для удаления
        SaI* node_for_remove = last_node->next;
        // Получаем строку
        char* name = node_for_remove->value;
        // Высвобождаем ноду от старых данных
        node_for_remove->value = nullptr;
        // Возвращаем строку
        return name;
    }

    uint32_t StringStorage::free(const char* name) {
        // Перебираем ноды
        SaI* last_node = start_node;
        while (last_node != nullptr) {
            if (strcmp(last_node->next->value, name) == 0) {
                // Получаем ноду строки для удаления
                SaI* node_for_remove = last_node->next;
                // Высвобождаем ноду от старых данных
                // Высвобождаем указатель на старую строку
                delete node_for_remove->value;
                // Зануляем ссылку на старую строку
                node_for_remove->value = nullptr;
                // Возвращаем ID
                return node_for_remove->id;
            }
            last_node = last_node->next;
        }
        // Если что-то пошло по одному месту то возвращаем 0
        return 0;
    }

    char* StringStorage::remove(uint32_t id) {
        // Перебираем ноды
        SaI* last_node = start_node;
        for (; id > 0; id--)
            last_node = last_node->next;
        // Получаем ноду строки для удаления
        SaI* node_for_remove = last_node->next;
        // Получаем строку
        char* name = node_for_remove->value;
        // Выпиливаем ноду из списка
        last_node->next = node_for_remove->next;
        // Высвобождаем память
        delete node_for_remove;
        // Возвращаем строку
        return name;
    }

    uint32_t StringStorage::remove(const char* name) {
        // Перебираем ноды
        SaI* last_node = start_node;
        while (last_node != nullptr) {
            if (strcmp(last_node->next->value, name) == 0) {
                // Получаем ноду строки для удаления
                SaI* node_for_remove = last_node->next;
                // Получаем ID
                uint32_t i = node_for_remove->id;
                // Выпиливаем ноду из списка
                last_node->next = node_for_remove->next;
                // Высвобождаем память
                delete node_for_remove->value;
                delete node_for_remove;
                // Возвращаем ID
                return i;
            }
            last_node = last_node->next;
        }
        // Если что-то пошло по одному месту то возвращаем 0
        return 0;
    }
}