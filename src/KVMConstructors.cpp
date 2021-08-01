#include <KVMConstructors.hpp>

using namespace DmN::KVM::ERROR;

namespace DmN::KVM {
    SSS* allocSSS(char **names, size_t size) {
        // Создаём хранилище строк
        SSS* storage = new SSS(size);
        // Пихаем имена
        while (size != 0)
            storage->addNew(names[--size]);
        // Возвращаем хранилище строк
        return storage;
    }

    DSS* allocDSS(char **names, size_t size) {
        // Создаём хранилище строк
        auto* storage = new DSS;
        // Пихаем имена
        while (size != 0)
            storage->addNew(names[--size]);
        // Возвращаем хранилище строк
        return storage;
    }

    CR tryCollect(GCObject* obj) {
        // Проверяем можно ли собрать объект
        if (obj->isCollectable) {
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

    inline void collect(GCObject* obj) {
        // Высвобождаем память
        delete obj;
    }
}