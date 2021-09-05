#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_HEAP_HPP
#define DMN_KVM_HEAP_HPP

#include "KVMESC.hpp"
#include <utility>

namespace DmN::KVM {
    /// Абстрактная куча
    DMN_KVM_E struct Heap {
        /*!
         * Добавляет новый класс в хип
         * @param clazz Класс для добавления
         * @return ID добавленного класса в хипе
         */
        virtual CI_t addNew(ClassBase *clazz) = 0;

        /*!
         * Добавляет новую структуру в хип
         * @param structure Структура для добавления
         * @return ID добавленной структуры в хипе
         */
        virtual CI_t addNew(StructBase *structure) = 0;

        /*!
         * Добавляет новый enum в хип
         * @param enum_ Enum для добавления
         * @return ID добавленного enum-а в хипе
         */
        virtual CI_t addNew(EnumBase *enum_) = 0;

        /*!
         * Добавляет новый класс в хип, если класс уже был добавлен то просто возвращает его ID
         * @param clazz Класс для добавления
         * @return ID добавленного класса
         */
        virtual CI_t add(ClassBase *clazz) = 0;

        /*!
         * Добавляет новую структуру в хип, если структура уже была добавлена то просто возвращает её ID
         * @param structure Структура для добавления
         * @return ID добавленного класса
         */
        virtual CI_t add(StructBase *structure) = 0;

        /*!
         * Добавляет новый enum в хип, если enum уже был добавлен то просто возвращает его ID
         * @param enum_ Enum для добавления
         * @return ID добавленного enum-а
         */
        virtual CI_t add(EnumBase *enum_) = 0;

        /*!
         * Заменяет уже существующий класс по ID на новый
         * @param clazz Класс который будет заменять нужный класс
         * @param id ID класса который нужно заменить
         * @return Заменённый (оригинальный) класс
         */
        virtual ClassBase *replace(ClassBase *clazz, CI_t id) = 0;

        /*!
         * Заменяет уже существующую структуру по ID на новую
         * @param structure Структура которая будет заменять новую структуру
         * @param id ID структуры которую нужно заменить
         * @return Заменённая (оригинальная) структура
         */
        virtual StructBase *replace(StructBase *structure, CI_t id) = 0;

        /*!
         * Заменяет уже существующий enum по ID на новый
         * @param enum_ Enum который будет заменять нужный enum
         * @param id ID enum-а который нужно заменить
         * @return Заменённый (оригинальный) enum
         */
        virtual EnumBase *replace(EnumBase *enum_, CI_t id) = 0;

        /*!
         * Удаляет объект из хипа
         * @param clazz Класс для удаления
         */
        virtual void remove(LLTNameble *obj) = 0;

        /*!
         * Удаляет (класс/структуру/enum) из хипа
         * @param id ID (класса/структуры/enum-а) для удаления
         * @return (Класс/Структуру/Enum) который был удалён
         */
        virtual LLTNameble *remove(CI_t id) = 0;

        /*!
         * Удаляет класс из хипа и высвобождает память из под него
         * @param clazz Класс для удаления
         */
        virtual void collect(ClassBase *clazz) = 0;

        /*!
         * Удаляет класс из хипа и высвобождает память из под него
         * @param id ID класса для удаления
         */
        virtual void collect(CI_t id) = 0;

        /*!
         * Получает ID объекта в хипе
         * @param Obj Объект ID которого нужно получить
         * @return ID класса (0 в случае неудачи)
         */
        virtual CI_t get(const LLTNameble *obj) = 0;

        /*!
         * Получает класс из хипа по его ID
         * @param id ID класса для получения
         * @return Нужный нам класс (nullptr в случае неудачи)
         */
        virtual LLTNameble *get(CI_t id) = 0;

        /*!
         * Добавляет объекты в текущий хип из другого
         * @param heap хип из которого мы будет добавлять объекты
         */
        virtual void operator+(const Heap *heap, SS* last_heap_strings,  const SS* strings);
    };
}

#endif /* DMN_KVM_HEAP_HPP */