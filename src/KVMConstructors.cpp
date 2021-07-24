#include <KVMConstructors.hpp>
#include <KVMTypes.hpp>

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
}