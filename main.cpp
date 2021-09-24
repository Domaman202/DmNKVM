#include <core/KVMNetwork.hpp>
#include <core/KVMVM.hpp>
#include <iostream>
#include <cstring>
#include <cassert>
#include <thread>

namespace DmN::KVM::testing {
    namespace Network {
        void networkTest();
    }

    namespace SR {
        void stackRegisterTest();
    }

    namespace SS {
        void stringStorageTest();
    }
}

int main(int argc, char* argv[]) {
    DmN::KVM::testing::Network::networkTest();
    DmN::KVM::testing::SR::stackRegisterTest();
    DmN::KVM::testing::SS::stringStorageTest();
}

namespace DmN::KVM::testing {
    inline void check(NWR nwr) {
        if (((BaseError) nwr) != SUCCESS)
            throw;
    }

    namespace SS {
        void stringStorageTest() {
            // !Старт!
            std::cout << "[2][S] хранилище строк" << std::endl;
            // Создаём хранилище строк
            DmN::KVM::SS* strings = new DmN::KVM::SSS(512);
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
        void networkTestS();
        void networkTestC();

        uint16_t port;

        void networkTest() {
            // !Старт!
            std::cout << "[0][S] сеть" << std::endl;
            // Указываем порт для тестов
            port = 228;
            // Создаём поток сервера
            std::thread server_thread(networkTestS);
            // Создаём поток клиента
            std::thread client_thread(networkTestC);
            // Подключаемся к потоку клиента
            client_thread.join();
            // Подключаемся к потоку сервера
            server_thread.join();
            // Если мы ещё не сдохли, то всё норм
            // !Конец!
            std::cout << "[0][C]" << std::endl;
        }

        void networkTestS() {
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
        }

        void networkTestC() {
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
        }
    }
}