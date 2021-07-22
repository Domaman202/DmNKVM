#include "DmNKVM.hpp"
#include "DmNSTD.cpp"
#include <stdint.h>

using namespace DmN::std;

namespace DmN::KVM {
    /// Хрень которая содержит имя
    struct Nameble {
        uint32_t name_id;
    };
    /// Name and ID
    struct NaI {
        NaI(char* name, uint32_t id) {
            this->name = name;
            this->id = id;
        }

        uint32_t id;
        char* name;
    };
    /// Хренилище имён
    class Name_storage {
        Node<NaI>* start_name;

        uint32_t addNewName(char* name) {
            Node<NaI>* last_name = start_name;
            while (last_name->next != nullptr)
                last_name = last_name->next;
            last_name->next = new Node<NaI>(new NaI(name, last_name->value->id++), nullptr);
            return last_name->value->id;
        }

        uint32_t addName(char* name) {
            // TODO: нужно сделать, это добавляет новое имя если оно ещё не существует в списке имён
        }

        char* getName(uint32_t id) {
            Node<NaI>* last_name = start_name;
            for (; id > 0; --id)
                last_name = last_name->next;
            return last_name->value->name;
        }

        uint32_t getId(char* name) {
            // TODO: нужно сделать, это возвращает ID имени
        }

        char* remove(uint32_t id) {
            Node<NaI>* last_name = start_name;
            for (; id > 0; id--)
                last_name = last_name->next;
            char* name = last_name->next->value->name;
            last_name->next = last_name->next->next;
            return name;
        }

        uint32_t remove(char* name) {
            // TODO: нужно сделать, это удаляет имя из списка и возвращает его ID
        }
    };
}