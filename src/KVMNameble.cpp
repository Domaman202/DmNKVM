#include <KVMNameble.hpp>

#include <cstring>

namespace DmN::KVM {
    uint32_t SSS::addNew(const char* name) {
        // Сохраняем имя в массив и инкрементируем текущий индекс
        this->data[++this->last_index] = name;
        // Возвращаем индекс имени
        return this->last_index - 1;
    }

    uint32_t SSS::add(const char* name) {
        // Перебираем имена
        for (size_t i = 0; i < this->size; i++)
            // Сравниваем имена
            if (strcmp(this->data[i], name) == 0)
                // Если имена одинаковы то возвращаем ID имени
                return i;
        // Добавляем новое имя если его нет
        return this->addNew(name);
    }

    inline const char* SSS::get(uint32_t id) {
        // Получаем имя по ID
        return this->data[id];
    }

    uint32_t SSS::get(const char* name) {
        // Перебираем имена
        for (size_t i = 0; i < this->size; i++)
            // Сравниваем имена
            if (strcmp(this->data[i], name) == 0)
                // Если имена одинаковы то возвращаем ID имени
                return i;
        // Если мы нихрена не нашли то возвращаем -1
        return -1;
    }

    const char* SSS::free(uint32_t id) {
        // Проверяем можем ли мы высвободить ячейку массива от имени
        if ((this->last_index - 1) == id) {
            // Если да то высвобождаем ячейку массива от имени
            // Получаем имя
            const char* name = this->data[id];
            // Стираем имя из массива
            this->data[--this->last_index] = nullptr;
            // Возвращае имя
            return name;
        }
        // Иначе просто возвращаем имя
        return this->get(id);
    }

    uint32_t SSS::free(const char* name) {
        // Получаем ID
        uint32_t id = this->get(name);
        // Проверяем можем ли мы высвободить ячейку массива от имени
        if ((this->last_index - 1) == id)
            // Высвобождаем ячейку массива от имени
            this->data[--this->last_index] = nullptr;
        // Возвращаем ID
        return id;
    }

    inline const char* SSS::remove(uint32_t id) {
        // Ссылаемся на функцию free
        return this->free(id);
    }

    inline uint32_t SSS::remove(const char* name) {
        // Ссылаемся на функцию free
        return this->free(name);
    }

    void SSS::clear() {
        this->last_index = 0;
        for (size_t i = 0; i < this->size; i++)
            delete this->data[i];
    }

    uint32_t DSS::addNew(const char* name) {
        // Перебираем ноды
        SaI* last_node = this->start_node;
        while (last_node->next != nullptr)
            last_node = last_node->next;
        // Пихаем новую ноду с новой строкой
        last_node->next = new SaI(const_cast<char*>(name), last_node->id++, nullptr);
        // Возвращаем ID новой строки
        return last_node->next->id;
    }

    uint32_t DSS::add(const char* name) {
        // Переменная для пустой ноды
        SaI* free_node = this->start_node;
        // Перебираем ноды
        SaI* last_node = this->start_node;
        while (last_node->next != nullptr) {
            // Проверяем на существование имени
            if (strcmp(last_node->value, name) == 0)
                // Возвращаем ID этого имени
                return last_node->id;
            // Перебираем ноды
            last_node = last_node->next;
            // Если нода пуста то сохраняем её
            if (free_node == this->start_node && last_node->value == nullptr)
                free_node = last_node;
        }
        // Проверяем на существование строки
        if (strcmp(last_node->value, name) == 0)
            // Возвращаем ID этой строки
            return last_node->id;
        // Пихаем новую ноду с новой строкой
        if (free_node == last_node) {
            // Если у нас нет свободной ноды то создаём новую и пихаем туда значение
            last_node->next = new SaI(const_cast<char*>(name), last_node->id++, nullptr);
            // Возвращаем ID новой строки
            return last_node->next->id;
        }
        // Иначе пихаем значение в свободную ноду
        free_node->value = const_cast<char*>(name);
        // Возвращаем ID новой строки
        return last_node->next->id;
    }

    const char* DSS::get(uint32_t id) {
        // Перебираем ноды
        SaI* last_node = this->start_node;
        for (; id > 0; --id)
            last_node = last_node->next;
        // Возвращаем строку полученную по ID
        return last_node->value;
    }

    uint32_t DSS::get(const char* name) {
        // Перебираем ноды
        SaI* last_node = this->start_node;
        while (last_node != nullptr) {
            // Сравниваем имена
            if (strcmp(last_node->value, name) == 0)
                // Если строки совпадают то возвращаем нужный ID
                return last_node->id;
            // Перебираем ноды дальше
            last_node = last_node->next;
        }
        // Если нихрена не нашли то возвращаем -1
        return -1;
    }

    const char* DSS::free(uint32_t id) {
        // Перебираем ноды
        SaI* last_node = this->start_node;
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

    uint32_t DSS::free(const char* name) {
        // Перебираем ноды
        SaI* last_node = this->start_node;
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

    const char* DSS::remove(uint32_t id) {
        // Перебираем ноды
        SaI* last_node = this->start_node;
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

    uint32_t DSS::remove(const char* name) {
        // Перебираем ноды
        SaI* last_node = this->start_node;
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

    void DSS::clear() {
        // Перебираем ноды
        SaI* last_node = this->start_node;
        while (last_node != nullptr) {
            // Высвобождаем память из под строки
            delete last_node->value;
            // Перебираем ноды
            SaI* old_node = last_node;
            last_node = last_node->next;
            // Высвобождаем память занятую нодой
            delete old_node;
        }
    }
}