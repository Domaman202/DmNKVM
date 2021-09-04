#include <KVMUtils.hpp>

using namespace DmN::KVM::Error;

namespace DmN::KVM {
    ClassBase* allocClass8B(SI_t name, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) {
        return new Class_8bit_t(name, modifier, fields, fieldsCount, methods, methodsCount, parents, parentsCount);
    }

    ClassBase* allocClass16B(SI_t name, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) {
        return new Class_16bit_t(name, modifier, fields, fieldsCount, methods, methodsCount, parents, parentsCount);
    }

    ClassBase* allocClass32B(SI_t name, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) {
        return new Class_32bit_t(name, modifier, fields, fieldsCount, methods, methodsCount, parents, parentsCount);
    }

    NSClassBase* allocNSClass8B(SI_t name, NSI_t ns, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) {
        return new NSClass_8bit_t(name, ns, modifier, fields, fieldsCount, methods, methodsCount, parents, parentsCount);
    }

    NSClassBase* allocNSClass16B(SI_t name, NSI_t ns, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) {
        return new NSClass_16bit_t(name, ns, modifier, fields, fieldsCount, methods, methodsCount, parents, parentsCount);
    }

    NSClassBase* allocNSClass32B(SI_t name, NSI_t ns, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods, uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) {
        return new NSClass_32bit_t(name, ns, modifier, fields, fieldsCount, methods, methodsCount, parents, parentsCount);
    }

    SS* allocSSS(char **names, size_t size) {
        // Создаём хранилище строк
        SSS* storage = new SSS(size);
        // Пихаем имена
        while (size != 0)
            storage->addNew(names[--size]);
        // Возвращаем хранилище строк
        return storage;
    }

    SS* allocDSS(char **names, size_t size) {
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
            // Если объект собирается проверяем кол-во ссылок
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