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
        void close() const {
            shutdown(_socket, 0);
            ::close(_socket);
        }
    };

    DMN_KVM_E class SocketConnection : public NetworkObject {
    public:
        /*!
         * Отправляет буфер
         * @param buf буфер для отправки
         * @param len размер буфера
         * @return TODO: ЯХЗ
         */
        inline ssize_t sendBuf(void* buf, size_t len) const {
            return send(_socket, buf, len, 0);
        }

        /*!
         * Отправляет msghdr
         * @param msg msghdr для отправки
         * @return TODO: ЯХЗ
         */
        inline ssize_t sendMsg(msghdr* msg) const {
            return sendmsg(_socket, msg, 0);
        }

        /*!
         * Читает входящие в буфер
         * @param buf буфер в который нужно записать входящие данные
         * @param len размер данных которые нужно записать
         * @return TODO: ЯХЗ
         */
        inline ssize_t readBuf(void* buf, size_t len) const {
            return recv(_socket, buf, len, 0);
        }

        /*!
         * Читает входящий msghdr
         * @param msg msghdr в который нужно читать входящие данные
         * @return TODO: ЯХЗ
         */
        inline ssize_t readMsg(msghdr* msg) const {
            return recvmsg(_socket, msg, 0);
        }
    };

    DMN_KVM_E class Client : public SocketConnection {
    public:
        Client(const std::string &address, bool ipv6, uint16_t port, NWR &result, int &error) {
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

        /*!
         * Пытаемся подключится к серверу
         * @param error код ошибки (!LOW LEVEL!)
         * @return Результат выполнения
         */
        inline NWR tryConnect(int &error) {
            if (connect(_socket, (sockaddr*) &addr, sizeof(addr)) < 0) [[unlikely]]
                return Error::CONNECT_ERROR;
            return (NWR) Error::SUCCESS;
        }
    };

    DMN_KVM_E class Server : public NetworkObject {
    public:
        Server(uint16_t port, NWR &result, int &error) {
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
            if ((error = bind(_socket, (sockaddr*) &addr, sizeof(addr))) < 0) [[unlikely]] {
                result = Error::SOCKET_BIND_ERROR;
                return;
            }

            result = (NWR) Error::SUCCESS;
        }

        Server(const std::string &address, bool ipv6, uint16_t port, NWR &result, int &error) {
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

            // Биндим сокет
            if ((error = bind(_socket, (sockaddr*) &addr, sizeof(addr))) < 0) [[unlikely]] {
                result = Error::SOCKET_BIND_ERROR;
                return;
            }

            result = (NWR) Error::SUCCESS;
        }

        /*!
         * Разрешаем подключение для n-го кол-во клиентов
         * @param i кол-во клиентов которые могут подключиться
         * @param error кол ошибки (!LOW LEVEL!)
         * @return Результат
         */
        NWR listen_(int i, int& error) {
            if ((error = listen(_socket, i)) < 0) [[unlikely]]
                return (NWR) Error::LISTEN_ERROR;
            return (NWR) Error::SUCCESS;
        }

        /*!
         * Принимаем соединение
         * @param result результат
         * @param error код ошибки (LOW LEVEL)
         * @return Объект описывающий соединение
         */
        SocketConnection* accept(NWR& result, int& error) {
            auto addr_size = sizeof(addr);
            if ((error = ::accept(_socket, (sockaddr*) &addr, (socklen_t*) &addr_size)) < 0) [[unlikely]] {
                result = (NWR) Error::ACCEPT_ERROR;
                return nullptr;
            }

            result = (NWR) Error::SUCCESS;

            auto connection = new SocketConnection();
            connection->_socket = error;
            return connection;
        }
    };
}

#endif //DMN_KVM_NETWORK_HPP