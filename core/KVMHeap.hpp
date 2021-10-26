#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_HEAP_HPP
#define DMN_KVM_HEAP_HPP

#include "KVMUtils.hpp"
#include <utility>

namespace DmN::KVM {
    /// Абстрактная куча
    struct Heap {
        /*!
         * Добавляет новый объект в хип
         * @param obj
         * @return ID добавленного объекта
         */
        virtual CI_t addNew(LLTNameble *obj) = 0;

        /*!
         * Добавляет новый объект в хип, если объект уже был добавлен то просто возвращает его ID
         * @param obj Объект для добавления
         * @return ID добавленного объекта
         */
        virtual CI_t add(LLTNameble *obj) = 0;

        /*!
         * Заменяет уже существующий объект по ID на новый
         * @param obj Объект который будет заменять нужный объект
         * @param id ID объекта который нужно заменить
         * @return Заменённый (оригинальный) объект
         */
        virtual LLTNameble *replace(LLTNameble *obj, CI_t id) = 0;

        /*!
         * Удаляет объект из хипа
         * @param obj Объект для удаления
         */
        virtual void remove(LLTNameble *obj) = 0;

        /*!
         * Удаляет объект из хипа
         * @param id ID объекта для удаления
         * @return Объект который был удалён
         */
        virtual LLTNameble *remove(CI_t id) = 0;

        /*!
         * Удаляет объект из хипа и высвобождает память из под него
         * @param obj Объект для удаления
         */
        virtual void collect(GCObject *obj) = 0;

        /*!
         * Удаляет объект из хипа и высвобождает память из под него
         * @param id ID объекта для удаления
         */
        virtual void collect(CI_t id) = 0;

        /*!
         * Получает ID объекта в хипе
         * @param Obj Объект ID которого нужно получить
         * @return ID объекта (0 в случае неудачи)
         */
        virtual CI_t get(const LLTNameble *obj) = 0;

        /*!
         * Получает объект из хипа по его ID
         * @param id ID класса для получения
         * @return Нужный нам объект (nullptr в случае неудачи)
         */
        virtual LLTNameble *get(CI_t id) = 0;

        /*!
         * Получает объект из хипа по его имени
         * @param id id строки имени объекта
         * @return Нужный нам объект (nullptr в случае неудачи)
         */
        virtual LLTNameble *getWN(SI_t id) = 0;
    };

    using namespace DmN::SDL;

    namespace internal::DHeap {
        struct OaI : public Node<LLTNameble *> {
            OaI(LLTNameble *obj, CI_t id, OaI *next) : Node<LLTNameble *>(obj, next) {
                this->next = next;
                this->id = id;
            }

            CI_t id;
            OaI *next;
        };
    }

    using namespace DmN::KVM::internal::DHeap;

    class DHeap : public Heap {
    public:
        OaI *start_node = new OaI(nullptr, 0, nullptr);

        DHeap() : Heap() {}

        ~DHeap() {
            OaI *last_node;
            for (last_node = this->start_node; last_node != nullptr;) {
                OaI *next_node = last_node->next;
                delete last_node->value;
                delete last_node;
                last_node = next_node;
            }
            delete last_node;
        }

        CI_t addNew(LLTNameble *obj) override {
            OaI *last_node = this->start_node;
            while (last_node->next != nullptr)
                last_node = last_node->next;
            last_node->next = new OaI(obj, last_node->id + 1, nullptr);
            return last_node->next->id;
        }

        CI_t add(LLTNameble *obj) override {
            OaI *last_node;
            for (last_node = this->start_node;; last_node = last_node->next) {
                if (last_node->value == obj)
                    return last_node->id;
                if (last_node->next == nullptr)
                    break;
            }
            last_node->next = new OaI(obj, last_node->id + 1, nullptr);
            return last_node->next->id;
        }

        LLTNameble *replace(LLTNameble *obj, CI_t id) override { // TODO: СУ
            OaI *last_node;
            for (last_node = this->start_node; last_node->id != id; last_node = last_node->next);
            LLTNameble *old = last_node->value;
            last_node->value = obj;
            return old;
        }

        void remove(LLTNameble *obj) override {
            OaI *prev_node;
            for (prev_node = this->start_node; prev_node->next->value != obj; prev_node = prev_node->next);
            prev_node->next = prev_node->next->next;
        }

        LLTNameble *remove(CI_t id) override {
            if (id == 0) {
                LLTNameble *val = this->start_node->value;
                delete this->start_node;
                return val;
            }
            OaI *prev_node;
            for (prev_node = this->start_node;
                 prev_node->next != nullptr && prev_node->next->id != id; prev_node = prev_node->next);
            OaI *node = prev_node->next;
            prev_node->next = prev_node->next->next;
            LLTNameble *obj = node->value;
            delete node;
            return obj;
        }

        void collect(CI_t id) override { // TODO:
            OaI *last_node;
            for (last_node = this->start_node; last_node->id != id; last_node = last_node->next);
#ifdef DMN_KVM_RTTI_COLLECT
            if (typeid(*last_node->value) == typeid(GCObject))
                Utils::tryCollect((GCObject *) last_node->value);
#else
            delete last_node->value;
#endif /* DMN_KVM_RTTI_COLLECT */
            delete last_node;
        }

        void collect(GCObject *obj) override { // TODO:
#ifdef DMN_KVM_RTTI_COLLECT
            if (typeid(*obj) == typeid(LLTNameble))
                this->remove((LLTNameble *) (obj));
#endif /* DMN_KVM_RTTI_COLLECT */
            Utils::tryCollect(obj);
        }

        CI_t get(const LLTNameble *obj) override {
            OaI *last_node = this->start_node;
            while (true) {
                if (last_node->value == obj)
                    return last_node->id;
                last_node = last_node->next;
            }
        }

        LLTNameble *get(CI_t id) override {
            OaI *last_node;
            for (last_node = this->start_node; last_node->id != id; last_node = last_node->next);
            return last_node->value;
        }

        LLTNameble *getWN(SI_t id) override {
            OaI *last_node;
            for (last_node = this->start_node->next; last_node->value->name != id; last_node = last_node->next) {
                if (last_node->next == nullptr)
                    return nullptr;
            }
            return last_node->value;
        }
    };
}

#endif /* DMN_KVM_HEAP_HPP */