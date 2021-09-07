#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_NAMEBLE_HPP
#define DMN_KVM_NAMEBLE_HPP

#include "KVMConfig.hpp"
#include "SDmNL.hpp"
#include <cstddef>
#include <cstdlib>
#include <utility>

namespace DmN::KVM {
    /// String and ID
    DMN_KVM_E struct SaI : SDL::Node<char*> {
        SaI(char* name, SI_t id, SaI* next) : SDL::Node<char*>(name, next) {
            this->id = id;
            this->next = next;
        }

        /// ID
        SI_t id;
        /// Следующий объект
        SaI* next;
    };

    /// Абстрактное хранилище строк
    DMN_KVM_E struct SS {
        /*!
         * Добавляет новую строку без проверки её существования, возвращает ID добавлянной строки
         * @param name имя которое нужно добавить
         * @return ID которое принадлежит имени
         */
        [[nodiscard]] virtual SI_t addNew(const char* name) = 0;

        /*!
         * Добавляет новую строку если она не существует, возвращает ID этой строки
         * @param name имя которое нужно добавить
         * @return ID которое принадлежит имени
         */
        [[nodiscard]] virtual SI_t add(const char* name) = 0;

        /*!
         * Получает имя по ID
         * @param id ID по которому мы получаем имя
         * @return Имя полученное по ID
         */
        [[nodiscard]] virtual const char* get(SI_t id) const = 0;

        /*!
         * Получаем ID по имени
         * @param name имя ID которого нужно получить
         * @return ID этого имени
         */
        [[nodiscard]] virtual SI_t get(const char* name) const = 0;

        /*!
         * Удаляем имя из списка по ID и возвращает само имя
         * (Сохраняет ноду для пере использования)
         * @param id ID которое нужно удалить
         * @return имя которое было удалено
         */
        virtual const char* free(SI_t id) = 0;

        /*!
         * Удаляет имя из списка и возвращает ID
         * (Удаляет ноду)
         * @param name имя для удаления
         * @return ID удалённого имени
         */
        virtual SI_t free(const char* name) = 0;

        /*!
         * Удаляем имя из списка по ID и возвращает само имя
         * (Удаляет ноду)
         * @param id ID которое нужно удалить
         * @return имя которое было удалено
         */
        virtual const char* remove(SI_t id) = 0;

        /*!
         * Удаляет имя из списка и возвращает ID
         * (Удаляет ноду)
         * @param name имя для удаления
         * @return ID удалённого имени
         */
        virtual SI_t remove(const char* name) = 0;

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
        [[nodiscard]] virtual SDL::List<std::pair<SI_t, SI_t>>* add(const SS* strings);
    };

    /// (Static String Storage) Статическое хранилище строк
    class SSS : public SS {
    protected:
        /// Массив ID и строк
        const char** data;
        /// Размер
        size_t _size;
        /// Текущий индекс
        size_t last_index = 0;
    public:
        explicit SSS(size_t size) {
            this->data = static_cast<const char**>(calloc(size, sizeof(char*)));
            this->_size = size;
        }

        [[nodiscard]] SI_t addNew(const char* name) override;
        [[nodiscard]] SI_t add(const char* name) override;
        [[nodiscard]] SI_t get(const char *name) const override;
        SI_t free(const char *name) override;
        SI_t remove(const char *name) override;
        [[nodiscard]] const char* get(SI_t id) const override;
        const char* free(SI_t id) override;
        const char* remove(SI_t id) override;
        void clear() override;
        [[nodiscard]] size_t size() const override;
    };

    /// (Dynamic String Storage) Динамическое хранилище строк
    class DSS : public SS {
    protected:
        /// Первая нода (всегда пуста)
        SaI* start_node = new SaI(nullptr, 0, nullptr);
    public:
        DSS() : SS() { }

        [[nodiscard]] SI_t addNew(const char* name) override;
        [[nodiscard]] SI_t add(const char* name) override;
        [[nodiscard]] SI_t get(const char *name) const override;
        SI_t free(const char *name) override;
        SI_t remove(const char *name) override;
        [[nodiscard]] const char * get(SI_t id) const override;
        const char * remove(SI_t id) override;
        const char * free(SI_t id) override;
        void clear() override;
        [[nodiscard]] size_t size() const override;
    };

    /// Хрень которая содержит имя
    DMN_KVM_E struct Nameble {
        explicit Nameble(SI_t name) {
            this->name = name;
        }

        /// ID имени
        SI_t name;
    };
}

#endif /* DMN_KVM_NAMEBLE_HPP */