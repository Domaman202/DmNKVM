#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_NAMEBLE_HPP
#define DMN_KVM_NAMEBLE_HPP

#include "SDmNL.hpp"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <utility>

namespace DmN::KVM {
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
        [[nodiscard]] virtual SDL::List<std::pair<SI_t, SI_t>> *add(const SS *strings) {
            auto *mappings = new SDL::List<std::pair<SI_t, SI_t>>
                    (nullptr);
            size_t i = strings->size();
            while (i != 0) {
                mappings->add(std::make_pair(i, this->add(strings->get(i--))));
            }
            return mappings;
        }
    };

    /// (Static String Storage) Статическое хранилище строк
    class SSS : public SS {
    public:
        /// Массив ID и строк
        const char **data;
        /// Размер
        size_t _size;
        /// Текущий индекс
        size_t last_index = 1;

        explicit SSS(size_t size) {
            this->data = new const char*[size] { "" };
            this->_size = size;
        }

        ~SSS() {
            delete[] this->data;
        }

        [[nodiscard]] SI_t addNew(const char *name) override {
            this->data[this->last_index++] = name;
            return this->last_index - 1;
        }

        [[nodiscard]] SI_t add(const char *name) override {
            for (size_t i = 1; i < this->last_index; i++)
                if (strcmp(this->data[i], name) == 0)
                    return i;
            return this->addNew(name);
        }

        [[nodiscard]] SI_t get(const char *name) const override {
            for (size_t i = 1; i < this->last_index; i++)
                if (strcmp(this->data[i], name) == 0)
                    return i;
            return -1;
        }

        [[nodiscard]] const char *get(SI_t id) const override {
            return this->data[id];
        }

        SI_t free(const char *name) override {
            uint32_t id = this->get(name);
            if ((this->last_index - 1) == id)
                this->data[--this->last_index] = nullptr;
            return id;
        }

        const char *free(SI_t id) override {
            if ((this->last_index - 1) == id) {
                const char *name = this->data[id];
                this->data[--this->last_index] = nullptr;
                return name;
            }
            return this->get(id);
        }

        SI_t remove(const char *name) override {
            return this->free(name);
        }

        inline const char *remove(SI_t id) override {
            return this->free(id);
        }

        void clear() override {
            this->last_index = 0;
            for (size_t i = 0; i < this->last_index; i++)
                delete this->data[i];
        }

        [[nodiscard]] inline size_t size() const override {
            return this->_size;
        }
    };

    namespace internal::DSS {
        /// String and ID
        struct SaI : public SDL::Node<char *> {
            SaI(char *name, SI_t id, SaI *next) : SDL::Node<char *>(name, next) {
                this->id = id;
                this->next = next;
            }

            /// ID
            SI_t id;
            /// Следующий объект
            SaI *next;
        };
    }

    using namespace internal::DSS;

    /// (Dynamic String Storage) Динамическое хранилище строк
    class DSS : public SS {
    public:
        /// Первая нода (всегда пуста)
        SaI *start_node = new SaI(nullptr, 0, nullptr);

        DSS() : SS() {}

        ~DSS() {
            SaI* last_node = this->start_node;
            while (last_node != nullptr) {
                SaI* next_node = last_node->next;
                delete last_node;
                last_node = next_node;
            }
            delete last_node;
        }

        [[nodiscard]] SI_t addNew(const char *name) override {
            SaI *last_node = this->start_node;
            while (last_node->next != nullptr)
                last_node = last_node->next;
            last_node->next = new SaI(const_cast<char *>(name), ++last_node->id, nullptr);
            return last_node->next->id;
        }

        [[nodiscard]] SI_t add(const char *name) override {
            SaI *free_node = this->start_node;
            SaI *last_node = this->start_node->next;
            if (last_node != nullptr) {
                while (last_node->next != nullptr) {
                    if (strcmp(last_node->value, name) == 0)
                        return last_node->id - 1;
                    last_node = last_node->next;
                    if (free_node == this->start_node && last_node->value == nullptr)
                        free_node = last_node;
                }
                if (last_node != this->start_node && strcmp(last_node->value, name) == 0)
                    return last_node->id;
            } else
                last_node = this->start_node;
            if (last_node == this->start_node || free_node == last_node) {
                last_node->next = new SaI(const_cast<char *>(name), ++last_node->id, nullptr);
                return last_node->next->id;
            }
            free_node->value = const_cast<char *>(name);
            return last_node->next->id;
        }

        [[nodiscard]] SI_t get(const char *name) const override {
            SaI *last_node = this->start_node;
            while (last_node != nullptr) {
                if (strcmp(last_node->value, name) == 0)
                    return last_node->id;
                last_node = last_node->next;
            }
            return -1;
        }

        [[nodiscard]] const char *get(SI_t id) const override {
            SaI *last_node = this->start_node;
            for (; id > 0; --id)
                last_node = last_node->next;
            return last_node->value;
        }

        SI_t free(const char *name) override {
            SaI *last_node = this->start_node;
            while (last_node != nullptr) {
                if (strcmp(last_node->next->value, name) == 0) {
                    SaI *node_for_remove = last_node->next;
                    delete node_for_remove->value;
                    node_for_remove->value = nullptr;
                    return node_for_remove->id;
                }
                last_node = last_node->next;
            }
            return 0;
        }

        const char *free(SI_t id) override {
            SaI *last_node = this->start_node;
            for (; id > 0; id--)
                last_node = last_node->next;
            SaI *node_for_remove = last_node->next;
            char *name = node_for_remove->value;
            node_for_remove->value = nullptr;
            return name;
        }

        SI_t remove(const char *name) override {
            SaI *last_node = this->start_node;
            while (last_node != nullptr) {
                if (strcmp(last_node->next->value, name) == 0) {
                    SaI *node_for_remove = last_node->next;
                    uint32_t i = node_for_remove->id;
                    last_node->next = node_for_remove->next;
                    delete node_for_remove->value;
                    delete node_for_remove;
                    return i;
                }
                last_node = last_node->next;
            }
            return 0;
        }

        const char *remove(SI_t id) override {
            SaI *last_node = this->start_node;
            for (id--; id > 0; id--)
                last_node = last_node->next;
            SaI *node_for_remove = last_node->next;
            char *name = node_for_remove->value;
            last_node->next = node_for_remove->next;
            delete node_for_remove;
            return name;
        }

        void clear() override {
            SaI *last_node = this->start_node;
            while (last_node != nullptr) {
                delete last_node->value;
                SaI *old_node = last_node;
                last_node = last_node->next;
                delete old_node;
            }
        }

        [[nodiscard]] size_t size() const override {
            size_t size = 0;
            SaI *last_node = this->start_node;
            while (last_node->next == nullptr) {
                last_node = last_node->next;
                size++;
            }
            return size;
        }
    };

    /// Хрень которая содержит имя
    struct Nameble {
        explicit Nameble(SI_t name) {
            this->name = name;
        }

        /// ID имени
        SI_t name;
    };
}

#endif /* DMN_KVM_NAMEBLE_HPP */