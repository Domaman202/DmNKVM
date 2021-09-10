#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_NETWORK_HPP
#define DMN_KVM_NETWORK_HPP

#include "KVMConfig.hpp"
#include "KVMError.hpp"
#include <arpa/inet.h>
#include <string>

using namespace DmN::KVM::Error;

namespace DmN::KVM::Network {
    DMN_KVM_E struct NetworkObject {
        sockaddr_in addr{};
        int _socket = 0;

        /*!
         * Закрывает соединение
         */
        void close() const;
    };

    DMN_KVM_E class SocketConnection : public NetworkObject {
    public:
        /*!
         * Отправляет буфер
         * @param buf буфер для отправки
         * @param len размер буфера
         * @return TODO: ЯХЗ
         */
        inline ssize_t sendBuf(void *buf, size_t len) const;

        /*!
         * Отправляет msghdr
         * @param msg msghdr для отправки
         * @return TODO: ЯХЗ
         */
        inline ssize_t sendMsg(msghdr *msg) const;

        /*!
         * Читает входящие в буфер
         * @param buf буфер в который нужно записать входящие данные
         * @param len размер данных которые нужно записать
         * @return TODO: ЯХЗ
         */
        inline ssize_t readBuf(void *buf, size_t len) const;

        /*!
         * Читает входящий msghdr
         * @param msg msghdr в который нужно читать входящие данные
         * @return TODO: ЯХЗ
         */
        inline ssize_t readMsg(msghdr *msg) const;
    };

    DMN_KVM_E class Client : public SocketConnection {
    public:
        /*!
         * Конструктор клиента
         * @param address ip сервера
         * @param ipv6 это IPv6 адрес?
         * @param port порт
         * @param result результат
         * @param error код ошибки (!LOW LEVEL!)
         */
        Client(const std::string &address, bool ipv6, uint16_t port, NWR &result, int &error);

        /*!
         * Пытаемся подключится к серверу
         * @param error код ошибки (!LOW LEVEL!)
         * @return Результат выполнения
         */
        NWR tryConnect(int &error);
    };

    DMN_KVM_E class Server : public NetworkObject {
    public:
        /*!
         * Конструктор сервера
         * @param port порт
         * @param result результат выполнения
         * @param error код ошибки (!LOW LEVEL!)
         */
        Server(uint16_t port, NWR &result, int &error);

        /*!
         * Конструктор сервера
         * @param address адрес клиента
         * @param ipv6 это IPv6 адрес?
         * @param port порт
         * @param result результат
         * @param error код ошибки (!LOW LEVEL!)
         */
        Server(const std::string &address, bool ipv6, uint16_t port, NWR &result, int &error);

        /*!
         * Разрешаем подключение для n-го кол-во клиентов
         * @param i кол-во клиентов которые могут подключиться
         * @param error кол ошибки (!LOW LEVEL!)
         * @return Результат
         */
        NWR listen(int i, int &error);

        /*!
         * Принимаем соединение
         * @param result результат
         * @param error код ошибки (LOW LEVEL)
         * @return Объект описывающий соединение
         */
        SocketConnection *accept(NWR &result, int &error);
    };
}

inline ssize_t DmN::KVM::Network::SocketConnection::sendBuf(void *buf, size_t len) const {
    return send(_socket, buf, len, 0);
}

inline ssize_t DmN::KVM::Network::SocketConnection::sendMsg(msghdr *msg) const {
    return sendmsg(_socket, msg, 0);
}

inline ssize_t DmN::KVM::Network::SocketConnection::readBuf(void *buf, size_t len) const {
    return recv(_socket, buf, len, 0);
}

inline ssize_t DmN::KVM::Network::SocketConnection::readMsg(msghdr *msg) const {
    return recvmsg(_socket, msg, 0);
}

#endif //DMN_KVM_NETWORK_HPP