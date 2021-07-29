#include <KVMConstructors.hpp>
#include <KVMTypes.hpp>

using namespace DmN::KVM::ERROR;

namespace DmN::KVM {
    DSS* allocDSS(char **names, size_t size) {
        // Создаём хранилище строк
        auto* storage = new DSS;
        // Пихаем имена
        size--;
        for (; size != 0; size--)
            storage->addNewName(names[size]);
        // Возвращаем хранилище строк
        return storage;
    }

    CR tryCollect(GC_Object* obj) {
        // Проверяем можно ли собрать объект
        if (obj->is_collectable) {
            // Если объект собираеться проверяем кол-во ссылок
            if (obj->references == 0) {
                // Высвобождаем память
                delete obj;
                // Выводим код успешного выполнения
                return CR::SUCCESS;
            }
            // Иначе выводим код ошибки
            return CR::OBJECT_REFERENCE_NOT_NULL;
        }
        // Иначе выводим код ошибки
        return CR::OBJECT_NO_COLLECTABLE;
    }

    inline void collect(GC_Object* obj) {
        // Высвобождаем память
        delete obj;
    }
}