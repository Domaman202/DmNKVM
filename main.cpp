#include <core/KVMNetwork.hpp>
#include <core/KVMVM.hpp>
#include <iostream>
#include <cstring>
#include <cassert>
#include <pthread.h>

namespace DmN::KVM::testing {
    inline void check(NWR nwr) {
        if (nwr != NWR::SUCCESS)
            throw;
    }

    namespace VM {
        void *print(void **args, size_t argc);

        void helloTest() {
            // !Старт!
            std::cout << "[4][S] Hello, VM" << std::endl;
            //
            using C = DmN::KVM::KBC::BC;
            //
            uint8_t code[]{
                    0xFF,
                    C::CNS,
                    'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0',
                    C::CNS,
                    'p', 'r', 'i', 'n', 't', '(', 'R', ')', 'V', '\0',
                    C::LFS,
                    0,
                    C::CGH,
                    0,
                    C::LPV,
                    (int8_t) KBC::Primitive::DOUBLE,
                    0x89, 0x41, 0x60, 0xE5, 0xD0, 0x6, 0x69, 0x40,
                    0,
                    C::LPV,
                    (int8_t) KBC::Primitive::INT32,
                    0x0, 0x0, 0x0, 0x2,
                    1,
                    C::ADD,
                    0, 1, 0,
                    C::LUPV,
                    0, 0,
                    C::LTS,
                    0
            };
            //
            auto *vm = new VMCA(code, sizeof(code), nullptr, 0);
            //
            SI_t printId = vm->mainContext->process->strings->add("print(R)V");
            vm->mainContext->process->heap->add(new NRMethod_t(print, printId));
            //
            void *result = vm->callMain();
            std::cout << "Call main result " << *(double *) result << std::endl;
            free(result);
            //
            delete vm;
            //
            std::cout << "[4][C]" << std::endl;
        }

        void *print(void **args, size_t argc) {
            auto context = ((ExecuteContext *) args[1]);
            std::cout << "[OutputStream] "
                      << context->process->strings->get(*(SI_t *) context->thread->stack->peekPop()) << std::endl;
            return nullptr;
        }
    }

    namespace Heap {
        void heapTest() {
            // !Старт!
            std::cout << "[3][S] хип" << std::endl;
            // Создаём хип
            auto *heap = new DHeap();
            // Тестим
            auto var0 = new Variable_t(0, (void *) 228, 3, false);
            auto var1 = new Variable_t(1, (void *) 202, 3, false);
            CI_t id0 = heap->addNew(var0);
            CI_t id1 = heap->add(var0);
            CI_t id2 = heap->add(var1);
            // Проверяем
            assert(id0 == id1);
            assert(id0 != id2);
            // Тестим
            heap->replace(var0, id2);
            heap->replace(var1, id1);
            // Проверяем
            assert(heap->get(id0) == var1);
            assert(heap->get(id1) == var1);
            assert(heap->get(id2) == var0);
            assert(heap->remove(id0) == var1);
            assert(heap->remove(id2) == var0);
            // Удаляем хип и прочие объекты
            delete heap;
            // !Конец!
            std::cout << "[3][C]" << std::endl;
        }
    }

    namespace SS {
        void test(DmN::KVM::SS *strings) {
            // Помещаем строки
            SI_t id0 = strings->add("Hello, World!");
            SI_t id1 = strings->addNew("DmN202");
            SI_t spam_id0 = strings->addNew("x");
            SI_t id2 = strings->add("Hello, World!");
            SI_t spam_id1 = strings->addNew("x");
            SI_t id3 = strings->add("Hello, World!");
            SI_t spam_id2 = strings->addNew("x");
            SI_t id4 = strings->add("Hello, World!");
            SI_t spam_id3 = strings->addNew("x");
            // Проверяем строки
            assert(strcmp(strings->get(id0), "Hello, World!") == 0);
            assert(strcmp(strings->remove(id1), "DmN202") == 0);
            assert(strcmp(strings->get(id2), "Hello, World!") == 0);
            assert(strcmp(strings->get(id3), "Hello, World!") == 0);
            assert(strcmp(strings->get(id4), "Hello, World!") == 0);
            // Проверяем ID
            assert(spam_id0 != spam_id1);
            assert(spam_id1 != spam_id2);
            assert(spam_id2 != spam_id3);
            assert(spam_id0 != spam_id3);
        }

        void stringStorageTest() {
            // !Старт!
            std::cout << "[2][S] хранилище строк" << std::endl;
            // Создаём статическое хранилище строк
            auto *sss = new DmN::KVM::SSS(512);
            // Тестим
            test(sss);
            // Удаляем хранилище строк
            delete sss;
            // Создаём динамическое хранилище строк
            auto *dss = new DmN::KVM::DSS();
            // Тестим
            test(dss);
            // Удаляем хранилище строк
            delete dss;
            // !Конец!
            std::cout << "[2][C]" << std::endl;
        }
    }

    namespace SR {
        void stackRegisterTest() {
            // !Старт!
            std::cout << "[1][S] стек & регистры" << std::endl;
            // Создаём стек
            DmN::KVM::Stack<int32_t> stack(nullptr);
            // Проверяем стек
            stack.push(12);
            stack.push(21);
            stack.push(33);
            assert(stack.peekPop() == 33);
            assert(stack.peek() == 21);
            stack.push(202);
            stack.push(213);
            stack.pop();
            assert(stack.peek() == 202);
            stack.pop();
            assert(stack.peekPop() == 21);
            stack.push(333);
            assert(stack.peekPop() == 333);
            // Создаём хранилище регистров
            DmN::KVM::Resisters registers(213);
            // Пишем регистры
            for (int i = 0; i < registers.size; i++)
                registers[i] = new int(i);
            // Проверяем регистры
            for (int i = 0; i < registers.size; i++)
                assert(*(int *) registers[i] == i);
            // !Конец!
            std::cout << "[1][C]" << std::endl;
        }
    }

    namespace Network {
        void* networkTestS(void*);

        void* networkTestC(void*);

        uint16_t port;

        void networkTest() {
            // !Старт!
            std::cout << "[0][S] сеть" << std::endl;
            // Указываем порт для тестов
            port = 228;
            // Создаём поток сервера
            pthread_t server_thread;
            pthread_create(&server_thread, nullptr, (void *(*)(void *))networkTestS, nullptr);
            // Создаём поток клиента
            pthread_t client_thread;
            pthread_create(&client_thread, nullptr, (void *(*)(void *))networkTestC, nullptr);
            // Подключаемся к потоку клиента
            pthread_join(client_thread, nullptr);
            // Подключаемся к потоку сервера
            pthread_join(server_thread, nullptr);
            // Если мы ещё не сдохли, то всё норм
            // !Конец!
            std::cout << "[0][C]" << std::endl;
        }

        void *networkTestS(void*) {
            // Переменные ошибки
            NWR nwr;
            DmN::KVM::Network::socket_t error;
            // Создаём сервер
            auto server = new DmN::KVM::Network::Server(port, nwr, error);
            check(nwr);
            // Запускаем просмотр клиентов
            check(server->listen(1, error));
            // Подключаемся к клиенту
            auto connection = server->accept(nwr, error);
            check(nwr);
            // Отправляем сообщение (с выравниванием до 1024 байт)
            auto chars = new char[14];
            strcpy(chars, "Hello, World!");
            connection->sendBuf(chars, 14);
            // Закрываем соединения
            nwr = connection->close();
            check(nwr);
            nwr = server->close();
            check(nwr);
            //
            return nullptr;
        }

        void* networkTestC(void*) {
            NWR nwr;
            DmN::KVM::Network::socket_t error;
            // Создаём клиент
            auto client = new DmN::KVM::Network::Client("0.0.0.0", false, port, nwr, error);
            check(nwr);
            // Коннектимся к серверу
            check(client->tryConnect(error));
            // Принимаем сообщение выровненное до 1024 байт и выводим его
            char *str = new char[14];
            client->readBuf(str, 14);
            assert(strcmp(str, "Hello, World!") == 0);
            delete[] str;
            // Закрываем соединение
            client->close();
            //
            return nullptr;
        }
    }
}

int main(int argc, char* argv[]) {
    DmN::KVM::testing::Network::networkTest(); // TODO: MINGW FIX
    DmN::KVM::testing::SR::stackRegisterTest();
    DmN::KVM::testing::SS::stringStorageTest();
    DmN::KVM::testing::Heap::heapTest();
    DmN::KVM::testing::VM::helloTest();
}