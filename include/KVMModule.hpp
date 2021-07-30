#pragma once
#ifndef DMNKVM_KVMMODULE_HPP
#define DMNKVM_KVMMODULE_HPP

#include <KVMConfig.hpp>

#include <cstdint>

namespace DmN::KVM {
    /// Пространство имён
    exStruct(Namespace) : Nameble {
        /// Предок
        Namespace* parent;
    };

    /// Модуль
    exStruct(Module) : Namespace {
        /// Классы

    };

    /// (Namespace Storage) Хранилище пространств имён
    exStruct(NSStorage) {
        /*!
         * Добавляет новое пространство имён
         * @param ns - пространство имён для добавления
         * @return ID нового пространства имён
         */
        virtual NSI_t addNew(Namespace* ns) = 0;

        /*!
         * Добавляет новое пространство имён, если оно уже существует то возвращает его ID
         * @param ns - пространство имён для добавления
         * @return ID пространства имён
         */
        virtual NSI_t add(Namespace* ns) = 0;

        /*!
         * Получает ID пространства имён
         * @param ns - пространство имён ID которого нужно получить
         * @return ID нужного нам пространства имён
         */
        virtual NSI_t get(Namespace* ns) = 0;

        /*!
         * Получает пространство имён по ID
         * @param id - ID для получаения пространства имён
         * @return Нужное пространство имён
         */
        virtual Namespace* get(NSI_t id) = 0;

        /*!
         * Удаляет пространство имён
         * @param ns - пространство имён для удаления
         * @return ID пространства имён
         */
        virtual NSI_t remove(Namespace* ns) = 0;

        /*!
         * Удаляет пространство имён по ID
         * @param id - ID пространства имён для удаления
         * @return удалённое пространство имён
         */
        virtual Namespace* remove(NSI_t id) = 0;

        /*!
         * Очищает хранилище
         */
        virtual void clear() = 0;
    };

    /// (Namespace Object) Объект который подчинаеться пространству имён
    exStruct(NSObject) {
        explicit NSObject(NSI_t ns) {
            this->ns = ns;
        }
        /// (Namespace ID) ID пространства имён
        NSI_t ns;
    };
}

#endif /* DMNKVM_KVMMODULE_HPP */