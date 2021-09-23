#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_NAMEBLE_HPP
#define DMN_KVM_NAMEBLE_HPP

#include "KVMConfig.hpp"
#include "SDmNL.hpp"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <utility>

namespace DmN::KVM {
    /// String and ID
    struct SaI : SDL::Node<char *> {
        SaI(char *name, SI_t id, SaI *next) : SDL::Node<char *>(name, next) {
            this->id = id;
            this->next = next;
        }

        /// ID
        SI_t id;
        /// Следующий объект
        SaI *next;
    };

    /// Абстрактное хранилище строк
    struct SS {
        /*!
         * Добавляет новую строку без проверки её существования, возвращает ID добавлянной строки
         * @param name имя которое нужно добавить
         * @return ID которое принадлежит имени
         */
        [[nodiscard]] virtual SI_t addNew(const char *name) = 0;

        /*!
         * Добавляет новую строку если она не существует, возвращает ID этой строки
         * @param name имя которое нужно добавить
         * @return ID которое принадлежит имени
         */
        [[nodiscard]] virtual SI_t add(const char *name) = 0;

        /*!
         * Получает имя по ID
         * @param id ID по которому мы получаем имя
         * @return Имя полученное по ID
         */
        [[nodiscard]] virtual const char *get(SI_t id) const = 0;

        /*!
         * Получаем ID по имени
         * @param name имя ID которого нужно получить
         * @return ID этого имени
         */
        [[nodiscard]] virtual SI_t get(const char *name) const = 0;

        /*!
         * Удаляем имя из списка по ID и возвращает само имя
         * (Сохраняет ноду для пере использования)
         * @param id ID которое нужно удалить
         * @return имя которое было удалено
         */
        virtual const char *free(SI_t id) = 0;

        /*!
         * Удаляет имя из списка и возвращает ID
         * (Удаляет ноду)
         * @param name имя для удаления
         * @return ID удалённого имени
         */
        virtual SI_t free(const char *name) = 0;

        /*!
         * Удаляем имя из списка по ID и возвращает само имя
         * (Удаляет ноду)
         * @param id ID которое нужно удалить
         * @return имя которое было удалено
         */
        virtual const char *remove(SI_t id) = 0;

        /*!
         * Удаляет имя из списка и возвращает ID
         * (Удаляет ноду)
         * @param name имя для удаления
         * @return ID удалённого имени
         */
        virtual SI_t remove(const char *name) = 0;

        /*!
         * Очищает данные
         */
        virtual void clear() = 0;

        /*!
         * Возвращает размер хранилища
         */
        [[nodiscard]] virtual size_t size() const = 0;

        /*!
         * Складывает 2 хранилища воедино
         */
        [[nodiscard]] virtual SDL::List<std::pair < SI_t, SI_t>> *

        add(const SS *strings);
    };

    /// (Static String Storage) Статическое хранилище строк
    class SSS : public SS {
    public:
        /// Массив ID и строк
        const char **data;
        /// Размер
        size_t _size;
        /// Текущий индекс
        size_t last_index = 0;

        explicit SSS(size_t size) {
            this->data = static_cast<const char **>(calloc(size, sizeof(char *)));
            this->_size = size;
        }

        [[nodiscard]] SI_t addNew(const char *name) override;

        [[nodiscard]] SI_t add(const char *name) override;

        [[nodiscard]] SI_t get(const char *name) const override;

        SI_t free(const char *name) override;

        SI_t remove(const char *name) override;

        [[nodiscard]] const char *get(SI_t id) const override;

        const char *free(SI_t id) override;

        const char *remove(SI_t id) override;

        void clear() override;

        [[nodiscard]] size_t size() const override;
    };

    /// (Dynamic String Storage) Динамическое хранилище строк
    class DSS : public SS {
    public:
        /// Первая нода (всегда пуста)
        SaI *start_node = new SaI(nullptr, 0, nullptr);

        DSS() : SS() {}

        [[nodiscard]] SI_t addNew(const char *name) override;

        [[nodiscard]] SI_t add(const char *name) override;

        [[nodiscard]] SI_t get(const char *name) const override;

        SI_t free(const char *name) override;

        SI_t remove(const char *name) override;

        [[nodiscard]] const char *get(SI_t id) const override;

        const char *remove(SI_t id) override;

        const char *free(SI_t id) override;

        void clear() override;

        [[nodiscard]] size_t size() const override;
    };

    /// Хрень которая содержит имя
    struct Nameble {
        explicit Nameble(SI_t name) {
            this->name = name;
        }

        /// ID имени
        SI_t name;
    };

    SDL::List<std::pair < SI_t, SI_t>>*

    SS::add(const SS *strings) {
        auto *mappings = new SDL::List<std::pair < SI_t, SI_t>>
        (nullptr);
        size_t i = strings->size();
        while (i != 0) {
            mappings->add(std::make_pair(i, this->add(strings->get(i--))));
        }
        return mappings;
    }

    uint32_t SSS::addNew(const char *name) {
        // Сохраняем имя в массив и инкриминируем текущий индекс
        this->data[++this->last_index] = name;
        // Возвращаем индекс имени
        return this->last_index - 1;
    }

    uint32_t SSS::add(const char *name) {
        // Перебираем имена
        for (size_t i = 0; i < this->_size; i++)
            // Сравниваем имена
            if (strcmp(this->data[i], name) == 0)
                // Если имена одинаковы то возвращаем ID имени
                return i;
        // Добавляем новое имя если его нет
        return this->addNew(name);
    }

    inline const char *SSS::get(uint32_t id) const {
        // Получаем имя по ID
        return this->data[id];
    }

    uint32_t SSS::get(const char *name) const {
        // Перебираем имена
        for (size_t i = 0; i < this->_size; i++)
            // Сравниваем имена
            if (strcmp(this->data[i], name) == 0)
                // Если имена одинаковы то возвращаем ID имени
                return i;
        // Если мы нихрена не нашли то возвращаем -1
        return -1;
    }

    const char *SSS::free(uint32_t id) {
        // Проверяем можем ли мы высвободить ячейку массива от имени
        if ((this->last_index - 1) == id) {
            // Если да то высвобождаем ячейку массива от имени
            // Получаем имя
            const char *name = this->data[id];
            // Стираем имя из массива
            this->data[--this->last_index] = nullptr;
            // Возвращае имя
            return name;
        }
        // Иначе просто возвращаем имя
        return this->get(id);
    }

    uint32_t SSS::free(const char *name) {
        // Получаем ID
        uint32_t id = this->get(name);
        // Проверяем можем ли мы высвободить ячейку массива от имени
        if ((this->last_index - 1) == id)
            // Высвобождаем ячейку массива от имени
            this->data[--this->last_index] = nullptr;
        // Возвращаем ID
        return id;
    }

    inline const char *SSS::remove(uint32_t id) {
        // Ссылаемся на функцию free
        return this->free(id);
    }

    inline uint32_t SSS::remove(const char *name) {
        // Ссылаемся на функцию free
        return this->free(name);
    }

    void SSS::clear() {
        this->last_index = 0;
        for (size_t i = 0; i < this->_size; i++)
            delete this->data[i];
    }

    inline size_t SSS::size() const {
        return this->_size;
    }

    uint32_t DSS::addNew(const char *name) {
        // Перебираем ноды
        SaI *last_node = this->start_node;
        while (last_node->next != nullptr)
            last_node = last_node->next;
        // Пихаем новую ноду с новой строкой
        last_node->next = new SaI(const_cast<char *>(name), last_node->id++, nullptr);
        // Возвращаем ID новой строки
        return last_node->next->id;
    }

    uint32_t DSS::add(const char *name) {
        // Переменная для пустой ноды
        SaI *free_node = this->start_node;
        // Перебираем ноды
        SaI *last_node = this->start_node;
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
            last_node->next = new SaI(const_cast<char *>(name), last_node->id++, nullptr);
            // Возвращаем ID новой строки
            return last_node->next->id;
        }
        // Иначе пихаем значение в свободную ноду
        free_node->value = const_cast<char *>(name);
        // Возвращаем ID новой строки
        return last_node->next->id;
    }

    const char *DSS::get(uint32_t id) const {
        // Перебираем ноды
        SaI *last_node = this->start_node;
        for (; id > 0; --id)
            last_node = last_node->next;
        // Возвращаем строку полученную по ID
        return last_node->value;
    }

    uint32_t DSS::get(const char *name) const {
        // Перебираем ноды
        SaI *last_node = this->start_node;
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

    const char *DSS::free(uint32_t id) {
        // Перебираем ноды
        SaI *last_node = this->start_node;
        for (; id > 0; id--)
            last_node = last_node->next;
        // Получаем ноду строки для удаления
        SaI *node_for_remove = last_node->next;
        // Получаем строку
        char *name = node_for_remove->value;
        // Высвобождаем ноду от старых данных
        node_for_remove->value = nullptr;
        // Возвращаем строку
        return name;
    }

    uint32_t DSS::free(const char *name) {
        // Перебираем ноды
        SaI *last_node = this->start_node;
        while (last_node != nullptr) {
            if (strcmp(last_node->next->value, name) == 0) {
                // Получаем ноду строки для удаления
                SaI *node_for_remove = last_node->next;
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

    const char *DSS::remove(uint32_t id) {
        // Перебираем ноды
        SaI *last_node = this->start_node;
        for (; id > 0; id--)
            last_node = last_node->next;
        // Получаем ноду строки для удаления
        SaI *node_for_remove = last_node->next;
        // Получаем строку
        char *name = node_for_remove->value;
        // Выпиливаем ноду из списка
        last_node->next = node_for_remove->next;
        // Высвобождаем память
        delete node_for_remove;
        // Возвращаем строку
        return name;
    }

    uint32_t DSS::remove(const char *name) {
        // Перебираем ноды
        SaI *last_node = this->start_node;
        while (last_node != nullptr) {
            if (strcmp(last_node->next->value, name) == 0) {
                // Получаем ноду строки для удаления
                SaI *node_for_remove = last_node->next;
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
        SaI *last_node = this->start_node;
        while (last_node != nullptr) {
            // Высвобождаем память из под строки
            delete last_node->value;
            // Перебираем ноды
            SaI *old_node = last_node;
            last_node = last_node->next;
            // Высвобождаем память занятую нодой
            delete old_node;
        }
    }

    size_t DSS::size() const {
        size_t size = 0;
        SaI *last_node = this->start_node;
        while (last_node->next == nullptr) {
            last_node = last_node->next;
            size++;
        }
        return size;
    }
}

#endif /* DMN_KVM_NAMEBLE_HPP */