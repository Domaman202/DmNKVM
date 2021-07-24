#include <KVMConstructors.hpp>
#include <KVMTypes.hpp>

using namespace DmN::KVM::ERROR;

namespace DmN::KVM {
    DynamicStringStorage* allocate_DynamicStringStorage(char* names[], size_t size) {
        // Создаём хранилище строк
        auto* storage = new DynamicStringStorage;
        // Пихаем имена
        size--;
        for (; size != 0; size--)
            storage->addNewName(names[size]);
        // Возвращаем хранилище строк
        return storage;
    }

    Collect_Result try_collect(GC_Object* obj) {
        // Проверяем можно ли собрать объект
        if (obj->is_collectable) {
            // Если объект собираеться проверяем кол-во ссылок
            if (obj->references == 0) {
                // Высвобождаем память
                delete obj;
                // Выводим код успешного выполнения
                return Collect_Result::SUCCESS;
            }
            // Иначе выводим код ошибки
            return Collect_Result::OBJECT_REFERENCE_NOT_NULL;
        }
        // Иначе выводим код ошибки
        return Collect_Result::OBJECT_NO_COLLECTABLE;
    }

    inline void collect(GC_Object* obj) {
        // Высвобождаем память
        delete obj;
    }
}