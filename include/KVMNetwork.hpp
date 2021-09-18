#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_NETWORK_HPP
#define DMN_KVM_NETWORK_HPP

#include "KVMConfig.hpp"
#include "KVMError.hpp"
#include <string>

using namespace DmN::KVM::Error;

namespace DmN::KVM::Network {
    class NetworkHandler {
        /// TODO:
    };

    /// Простой сетевой объект
    struct NetworkObject {
        sockaddr_in addr{};
        socket_t _socket = 0;

        /*!
         * Закрывает соединение
         */
        void close() const;
    };

    /// Сокетовое соединение
    class SocketConnection : public NetworkObject {
    public:
        /*!
         * Отправляет буфер
         * @param buf буфер для отправки
         * @param len размер буфера
         * @return TODO: ЯХЗ
         */
        inline size_t sendBuf(void *buf, packet_size_t len) const;

        /*!
         * Читает входящие в буфер
         * @param buf буфер в который нужно записать входящие данные
         * @param len размер данных которые нужно записать
         * @return TODO: ЯХЗ
         */
        inline size_t readBuf(void *buf, packet_size_t len) const;
    };

    /// Клиент
    class Client : public SocketConnection {
    public:
        /*!
         * Конструктор клиента
         * @param address ip сервера
         * @param ipv6 это IPv6 адрес?
         * @param port порт
         * @param result результат
         * @param error код ошибки (!LOW LEVEL!)
         */
        Client(const std::string &address, bool ipv6, uint16_t port, NWR &result, socket_t &error);

/*!
         * Пытаемся подключится к серверу
         * @param error код ошибки (!LOW LEVEL!)
         * @return Результат выполнения
         */
        NWR tryConnect(socket_t &error);
    };

    /// Сервер
    class Server : public NetworkObject {
    public:
        /*!
         * Конструктор сервера
         * @param port порт
         * @param result результат выполнения
         * @param error код ошибки (!LOW LEVEL!)
         */
        Server(uint16_t port, NWR &result, socket_t &error);

        /*!
         * Конструктор сервера
         * @param address адрес клиента
         * @param ipv6 это IPv6 адрес?
         * @param port порт
         * @param result результат
         * @param error код ошибки (!LOW LEVEL!)
         */
        Server(const std::string &address, bool ipv6, uint16_t port, NWR &result, socket_t &error);

        /*!
         * Разрешаем подключение для n-го кол-во клиентов
         * @param i кол-во клиентов которые могут подключиться
         * @param error кол ошибки (!LOW LEVEL!)
         * @return Результат
         */
        NWR listen(int i, socket_t &error);

        /*!
         * Принимаем соединение
         * @param result результат
         * @param error код ошибки (LOW LEVEL)
         * @return Объект описывающий соединение
         */
        SocketConnection *accept(NWR &result, socket_t &error);
    };

    inline size_t DmN::KVM::Network::SocketConnection::sendBuf(void *buf, packet_size_t len) const {
        return send(_socket, DMN_KVM_NETWORK_CAST_TO_BUFFER(buf), len, 0);
    }

    inline size_t DmN::KVM::Network::SocketConnection::readBuf(void *buf, packet_size_t len) const {
        return recv(_socket, DMN_KVM_NETWORK_CAST_TO_BUFFER(buf), len, 0);
    }

    void NetworkObject::close() const {
#ifdef WIN32
        closesocket(_socket);
#else
        shutdown(_socket, 0);
        ::close(_socket);
#endif /* WIN32 */
    }

    Client::Client(const std::string &address, bool ipv6, uint16_t port, NWR &result, socket_t &error) {
        // Проверка на ipv6
        int ip_protocol = ipv6 ? AF_INET6 : AF_INET;

        // Создаём сокет
        if ((_socket = socket(ip_protocol, SOCK_STREAM, PF_UNSPEC)) < 0) [[unlikely]] {
            result = Error::SOCKET_CREATE_ERROR;
            error = _socket;
            return;
        }

        // Выставляет сетевые параметры
        addr.sin_family = ip_protocol;
        addr.sin_port = port;
        if ((error = inet_pton(ip_protocol, address.c_str(), &(addr.sin_addr))) != 1) [[unlikely]] {
            result = Error::IP_CONVERT_ERROR;
            return;
        }

        // Если мы ещё не померли, то возвращаем хороший результат
        result = (NWR) Error::SUCCESS;
        error = 0;
    }

    NWR Client::tryConnect(socket_t &error) {
        if (connect(_socket, (sockaddr *) &addr, sizeof(addr)) < 0) [[unlikely]]
            return Error::CONNECT_ERROR;
        return (NWR) Error::SUCCESS;
    }

    Server::Server(uint16_t port, NWR &result, socket_t &error) {
        // Создаём сокет
        if ((_socket = socket(AF_INET, SOCK_STREAM, PF_UNSPEC)) < 0) [[unlikely]] {
            result = Error::SOCKET_CREATE_ERROR;
            error = _socket;
            return;
        }

        // Выставляет сетевые параметры
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = port;

        // Биндим сокет
        if ((error = bind(_socket, (sockaddr *) &addr, sizeof(addr))) < 0) [[unlikely]] {
            result = Error::SOCKET_BIND_ERROR;
            return;
        }

        result = (NWR) Error::SUCCESS;
    }

    Server::Server(const std::string &address, bool ipv6, uint16_t port, NWR &result, socket_t &error) {
        // Проверка на ipv6
        INT ip_protocol = ipv6 ? AF_INET6 : AF_INET;

        // Создаём сокет
        if ((_socket = socket(ip_protocol, SOCK_STREAM, PF_UNSPEC)) < 0) [[unlikely]] {
            result = Error::SOCKET_CREATE_ERROR;
            error = _socket;
            return;
        }

        // Выставляет сетевые параметры
        addr.sin_family = ip_protocol;
        addr.sin_port = port;
        if ((error = inet_pton(ip_protocol, address.c_str(), &(addr.sin_addr))) != 1) [[unlikely]] {
            result = Error::IP_CONVERT_ERROR;
            return;
        }

        // Биндим сокет
        if ((error = bind(_socket, (sockaddr *) &addr, sizeof(addr))) < 0) [[unlikely]] {
            result = Error::SOCKET_BIND_ERROR;
            return;
        }

        // Если всё зашибись, то выставляем соответствующий результат
        result = (NWR) Error::SUCCESS;
    }

    NWR Server::listen(int i, socket_t &error) {
        if ((error = ::listen(_socket, i)) < 0) [[unlikely]]
            return (NWR) Error::LISTEN_ERROR;
        return (NWR) Error::SUCCESS;
    }

    SocketConnection *Server::accept(NWR &result, socket_t &error) {
        auto addr_size = sizeof(addr);
#ifdef WIN32
        if ((error = ::accept(_socket, (sockaddr *) &addr, (int *) &addr_size)) < 0) [[unlikely]] {
            result = (NWR) Error::CONNECT_ACCEPT_ERROR;
            return nullptr;
        }
#else
        if ((error = ::accept(_socket, (sockaddr *) &addr, (socklen_t *) &addr_size)) < 0) [[unlikely]] {
            result = (NWR) Error::CONNECT_ACCEPT_ERROR;
            return nullptr;
        }
#endif /* WIN32 */

        result = (NWR) Error::SUCCESS;

        auto connection = new SocketConnection();
        connection->_socket = error;
        return connection;
    }
}

#endif //DMN_KVM_NETWORK_HPP