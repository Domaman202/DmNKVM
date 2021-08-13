#ifndef DMN_KVM_NO_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_HEAP_HPP
#define DMN_KVM_HEAP_HPP

#include <KVMConfig.hpp>
#include <KVMESC.hpp>

#include <utility>

namespace DmN::KVM {
    /// Абстрактная куча
    DMN_KVM_ES(Heap) {
        /*!
         * Добавляет новый класс в хип
         * @param clazz Класс для добавления
         * @return ID добавленного класса в хипе
         */
        virtual CI_t addNew(ClassBase* clazz) = 0;

        /*!
         * Добавляет новый класс в хип, если класс уже был добавлен то просто возвращает его ID
         * @param clazz Класс для добавления
         * @return ID добавленного класса
         */
        virtual CI_t add(ClassBase* clazz) = 0;

        /*!
         * Заменяет уже существующий класс по ID на новый
         * @param clazz Класс который будет заменять нужный класс
         * @param id ID класса который нужно заменить
         * @return Заменённый (оригинальный) класс
         */
        virtual ClassBase* replace(ClassBase* clazz, CI_t id) = 0;

        /*!
         * Удаляет класс из хипа
         * @param clazz Класс для удаления
         */
        virtual void remove(ClassBase* clazz) = 0;

        /*!
         * Удаляет класс из хипа
         * @param id ID класса для удаления
         * @return Класс который был удалён
         */
        virtual ClassBase* remove(CI_t id) = 0;

        /*!
         * Удаляет класс из хипа и высвобождает память из под него
         * @param clazz Класс для удаления
         */
        virtual void collect(ClassBase* clazz) = 0;

        /*!
         * Удаляет класс из хипа и высвобождает память из под него
         * @param id ID класса для удаления
         */
        virtual void collect(CI_t id) = 0;

        /*!
         * Получает ID класса в хипе
         * @param clazz Класс ID которого нужно получить
         * @return ID класса (0 в случае неудачи)
         */
        virtual CI_t get(ClassBase* clazz) = 0;

        /*!
         * Получает класс из хипа по его ID
         * @param id ID класса для получения
         * @return Нужный нам класс (nullptr в случае неудачи)
         */
        virtual ClassBase* get(CI_t id) = 0;

        //\\

        /*!
         * Получает предков класса
         * @param clazz Класс предков которого нужно получить
         * @return Пара [массив предков, кол-во предков] данного класса
         */
        virtual SDL::pair<ClassBase**, size_t> getParents(ClassBase* clazz) = 0;

        /*!
         * Получает предков класса
         * @param clazz ID класса в хипе предков которого нужно получить
         * @return Пара [массив предков, кол-во предков] данного класса
         */
        virtual SDL::pair<ClassBase**, size_t> getParents(CI_t clazz) = 0;
    };
}

#endif /* DMN_KVM_HEAP_HPP */