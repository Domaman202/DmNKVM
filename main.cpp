#include <KVMNetwork.hpp>
#include <KVMSR.hpp>
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
}

int main(int argc, char* argv[]) {
    DmN::KVM::testing::Network::networkTest();
    DmN::KVM::testing::SR::stackRegisterTest();
}

namespace DmN::KVM::testing {
    inline void check(NWR nwr) {
        if (((BaseError) nwr) != SUCCESS)
            throw;
    }

    namespace SR {
        void stackRegisterTest() {
            // !Старт!
            std::cout << "Старт проверки стека и регистров!" << std::endl;
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
            std::cout << "Успешно выполнена проверка стека и регистров!" << std::endl;
        }
    }

    namespace Network {
        void networkTestS();
        void networkTestC();

        uint16_t port;

        void networkTest() {
            // !Старт!
            std::cout << "Старт проверки сети!" << std::endl;
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
            std::cout << "Успешно выполнена проверка сети!" << std::endl;
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