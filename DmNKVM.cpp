#include "DmNKVM.hpp"
#include "DmNSTD.cpp"
#include <cstdint>
#include <cstring>

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
    class NameStorage {
        Node<NaI>* start_node;

        uint32_t addNewName(char* name) {
            Node<NaI>* last_node = start_node;
            while (last_node->next != nullptr)
                last_node = last_node->next;
            last_node->next = new Node<NaI>(new NaI(name, last_node->value->id++), nullptr);
            return last_node->value->id;
        }

        uint32_t addName(char* name) {
            // TODO: нужно сделать, это добавляет новое имя если оно ещё не существует в списке имён
        }

        char* getName(uint32_t id) {
            Node<NaI>* last_node = start_node;
            for (; id > 0; --id)
                last_node = last_node->next;
            return last_node->value->name;
        }

        uint32_t getId(char* name) {
            Node<NaI>* last_node = start_node;
            while (last_node->next != nullptr) {
                if (strcmp(last_node->value->name, name) == 0)
                    return last_node->value->id;
                last_node = last_node->next;
            }
            return 0;
        }

        char* remove(uint32_t id) {
            Node<NaI>* last_node = start_node;
            for (; id > 0; id--)
                last_node = last_node->next;
            char* name = last_node->next->value->name;
            last_node->next = last_node->next->next;
            return name;
        }

        uint32_t remove(char* name) {
            Node<NaI>* last_node = start_node;
            while (last_node->next != nullptr) {
                if (strcmp(last_node->next->value->name, name) == 0) {
                    uint32_t i = last_node->next->value->id;
                    last_node->next = last_node->next->next;
                    return i;
                }
                last_node = last_node->next;
            }
            return 0;
        }
    };
}