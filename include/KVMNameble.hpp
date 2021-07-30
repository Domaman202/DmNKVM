#pragma once
#ifndef DMNKVM_KVMNAMEBLE_HPP
#define DMNKVM_KVMNAMEBLE_HPP

#include <DmNSTD.hpp>
#include <KVMConfig.hpp>

#include <cstddef>
#include <cstdlib>

namespace DmN::KVM {
    /// String and ID
    exStruct(SaI) : std::Node<char> {
        SaI(char* name, SI_t id, SaI* next) : std::Node<char>(name, next) {
            this->id = id;
            this->next = next;
        }

        /// ID
        SI_t id;
        /// Следующий объект
        SaI* next;
    };

    /// Абстрактное хранилище строк
    exStruct(SS) {
    public:
        /*!
         * Добавляет новую строку без проверки её существования, возвращает ID добавлянной строки
         * \param name - имя которое нужно добавить
         * \return ID которое принадлежит имени
         */
        virtual SI_t addNew(const char* name) = 0;

        /*!
         * Добавляет новую строку если она не существует, возвращает ID этой строки
         * \param name - имя которое нужно добавить
         * \return ID которое принадлежит имени
         */
        virtual SI_t add(const char* name) = 0;

        /*!
         * Получает имя по ID
         * \param id - ID по которому мы получаем имя
         * \return Имя полученное по ID
         */
        virtual const char* get(SI_t id) = 0;

        /*!
         * Получаем ID по имени
         * \param name - имя ID которого нужно получить
         * \return ID этого имени
         */
        virtual SI_t get(const char* name) = 0;

        /*!
         * Удаляем имя из списка по ID и возвращает само имя
         * (Сохраняет ноду для переиспользования)
         * \param id ID которое нужно удалить
         * \return имя которое было удалено
         */
        virtual const char* free(SI_t id) = 0;

        /*!
         * Удаляет имя из списка и возвращает ID
         * (Удаляет ноду)
         * \param name - имя для удаления
         * \return ID удалённого имени
         */
        virtual SI_t free(const char* name) = 0;

        /*!
         * Удаляем имя из списка по ID и возвращает само имя
         * (Удаляет ноду)
         * \param id ID которое нужно удалить
         * \return имя которое было удалено
         */
        virtual const char* remove(SI_t id) = 0;

        /*!
         * Удаляет имя из списка и возвращает ID
         * (Удаляет ноду)
         * \param name - имя для удаления
         * \return ID удалённого имени
         */
        virtual SI_t remove(const char* name) = 0;

        /*!
         * Очищает данные
         */
        virtual void clear() = 0;
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
    exStruct(Nameble) {
        explicit Nameble(SI_t name) {
            this->name = name;
        }

        /// ID имени
        SI_t name;
    };
}

#endif /* DMNKVM_KVMNAMEBLE_HPP */