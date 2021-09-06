#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_NETWORK_HPP
#define DMN_KVM_NETWORK_HPP

#include "KVMConfig.hpp"
#include "KVMError.hpp"
#include <string>
#include <arpa/inet.h>

using namespace DmN::KVM::Error;

namespace DmN::KVM::Network {
    class Server {
    };

    class Client {
    protected:
        sockaddr_in s_addr{};
        int _socket = 0;
        int reader = 0;
    public:
        Client(const std::string &address, bool ipv6, uint16_t port, NWR &result, int &error) {
            // Проверка на ipv6
            int ip_protocol = ipv6 ? AF_INET6 : AF_INET;

            // Создаём сокет
            if ((_socket = socket(ip_protocol, SOCK_STREAM, PF_UNSPEC)) < 0) {
                result = Error::SOCKET_CREATE_ERROR;
                error = obj_socket;
                return;
            }

            // Выставляет сетевые параметры
            s_addr.sin_family = ip_protocol;
            s_addr.sin_port = port;
            if ((error = inet_pton(ip_protocol, address, &(s_addr.sin_addr))) != 1) {
                result = Error::IP_CONVERT_ERROR;
                return;
            }

            // Если мы ещё не померли, то возвращаем хороший результат
            result = Error::SUCCESS;
            error = 0;
        }

        inline NWR connect(int &error) {
            if (connect(_socket, &s_addr, sizeof(s_addr)) < 0) [[unlikely]]
                return Error::CONNECT_ERROR;
            return (NWR) Error::SUCCESS;
        }
    };
}

#endif //DMN_KVM_NETWORK_HPP