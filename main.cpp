#include <KVMNetwork.hpp>
#include <thread>
#include <iostream>
#include <cstring>

#define NO_THROW

using namespace DmN::KVM::Network;

uint16_t __PORT__;

void check(NWR);
void networkTestS();
void networkTestC();

int main(int argc, char* argv[]) {
    // Указываем порт для тестов
    __PORT__ = 228;
    // Создаём поток сервера
    std::thread server_thread(networkTestS);
    // Создаём поток клиента
    std::thread client_thread(networkTestC);
    // Подключаемся к потоку клиента
    client_thread.join();
    // Подключаемся к потоку сервера
    server_thread.join();
    // Если мы ещё не сдохли, то всё норм, возвращаем 0
    return 0;
}

void networkTestS() {
    // Переменные ошибки
    NWR nwr;
    int error;
    // Создаём сервер
    auto server = new Server(__PORT__, nwr, error);
    check(nwr);
    // Запускаем просмотр клиентов
    check(server->listen_(1, error));
    // Подключаемся к клиенту
    auto connection = server->accept(nwr, error);
    check(nwr);
    // Отправляем сообщение (с выравниванием до 1024 байт)
    auto chars = new char[1024];
    strcpy(chars, "Hello, World!");
    connection->sendBuf(chars, 1024);
    // Закрываем соединения
    connection->close();
    server->close();
}

void networkTestC() {
    NWR nwr;
    int error;
    // Создаём клиент
    auto client = new Client("0.0.0.0", false, __PORT__, nwr, error);
    check(nwr);
    // Коннектимся к серверу
    check(client->tryConnect(error));
    // Принимаем сообщение выровненное до 1024 байт и выводим его
    char* str = new char[1024];
    client->readBuf(str, 1024);
    std::cout << str << std::endl;
    delete[] str;
    // Закрываем соединение
    client->close();
}

inline void check(NWR nwr) {
#ifndef NO_THROW
    if (nwr != DmN::KVM::Error::SUCCESS)
        throw;
#endif /* NO_THROW */
}