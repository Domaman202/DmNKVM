#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_NAMEBLE_HPP
#define DMN_KVM_NAMEBLE_HPP

#include "KVMConfig.hpp"
#include "SDmNL.hpp"
#include <cstddef>
#include <cstdlib>

namespace DmN::KVM {
    /// String and ID
    DMN_KVM_E struct SaI : SDL::Node<char> {
        SaI(char* name, SI_t id, SaI* next) : SDL::Node<char>(name, next) {
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
        DMN_KVM_E virtual SI_t addNew(const char* name) = 0;

        /*!
         * Добавляет новую строку если она не существует, возвращает ID этой строки
         * @param name имя которое нужно добавить
         * @return ID которое принадлежит имени
         */
        DMN_KVM_E virtual SI_t add(const char* name) = 0;

        /*!
         * Получает имя по ID
         * @param id ID по которому мы получаем имя
         * @return Имя полученное по ID
         */
        DMN_KVM_E virtual const char* get(SI_t id) = 0;

        /*!
         * Получаем ID по имени
         * @param name имя ID которого нужно получить
         * @return ID этого имени
         */
        DMN_KVM_E virtual SI_t get(const char* name) = 0;

        /*!
         * Удаляем имя из списка по ID и возвращает само имя
         * (Сохраняет ноду для пере использования)
         * @param id ID которое нужно удалить
         * @return имя которое было удалено
         */
        DMN_KVM_E virtual const char* free(SI_t id) = 0;

        /*!
         * Удаляет имя из списка и возвращает ID
         * (Удаляет ноду)
         * @param name имя для удаления
         * @return ID удалённого имени
         */
        DMN_KVM_E virtual SI_t free(const char* name) = 0;

        /*!
         * Удаляем имя из списка по ID и возвращает само имя
         * (Удаляет ноду)
         * @param id ID которое нужно удалить
         * @return имя которое было удалено
         */
        DMN_KVM_E virtual const char* remove(SI_t id) = 0;

        /*!
         * Удаляет имя из списка и возвращает ID
         * (Удаляет ноду)
         * @param name имя для удаления
         * @return ID удалённого имени
         */
        DMN_KVM_E virtual SI_t remove(const char* name) = 0;

        /*!
         * Очищает данные
         */
        DMN_KVM_E virtual void clear() = 0;

        /*!
         * Складывает 2 хранилища строк воедино
         */
        operator+(SS* strings) = 0; // TODO:
    };

    /// (Static String Storage) Статическое хранилище строк
    class SSS : public SS {
    protected:
        /// Массив ID и строк
        const char** data;
        /// Размер
        size_t size;
        /// Текущий индекс
        size_t last_index = 0;
    public:
        explicit SSS(size_t size) {
            this->data = static_cast<const char**>(calloc(size, sizeof(char*)));
            this->size = size;
        }

        SI_t addNew(const char* name) override;
        SI_t add(const char* name) override;
        SI_t get(const char *name) override;
        SI_t free(const char *name) override;
        SI_t remove(const char *name) override;
        const char* get(SI_t id) override;
        const char* free(SI_t id) override;
        const char* remove(SI_t id) override;
        void clear() override;
    };

    /// (Dynamic String Storage) Динамическое хранилище строк
    class DSS : public SS {
    protected:
        /// Первая нода (всегда пуста)
        SaI* start_node = new SaI(nullptr, 0, nullptr);
    public:
        DSS() : SS() { }

        SI_t addNew(const char* name) override;
        SI_t add(const char* name) override;
        SI_t get(const char *name) override;
        SI_t free(const char *name) override;
        SI_t remove(const char *name) override;
        const char * get(SI_t id) override;
        const char * remove(SI_t id) override;
        const char * free(SI_t id) override;
        void clear() override;
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