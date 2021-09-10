#include <KVMNetwork.hpp>

namespace DmN::KVM::Network {
    void NetworkObject::close() const {
        shutdown(_socket, 0);
        ::close(_socket);
    }

    Client::Client(const std::string &address, bool ipv6, uint16_t port, NWR &result, int &error) {
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

    NWR Client::tryConnect(int &error) {
        if (connect(_socket, (sockaddr *) &addr, sizeof(addr)) < 0) [[unlikely]]
            return Error::CONNECT_ERROR;
        return (NWR) Error::SUCCESS;
    }

    Server::Server(uint16_t port, NWR &result, int &error) {
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

    Server::Server(const std::string &address, bool ipv6, uint16_t port, NWR &result, int &error) {
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
        if ((error = bind(_socket, (sockaddr *) &addr, sizeof(addr))) < 0) [[unlikely]] {
            result = Error::SOCKET_BIND_ERROR;
            return;
        }

        // Если всё зашибись, то выставляем соответствующий результат
        result = (NWR) Error::SUCCESS;
    }

    NWR Server::listen(int i, int &error) {
        if ((error = ::listen(_socket, i)) < 0) [[unlikely]]
            return (NWR) Error::LISTEN_ERROR;
        return (NWR) Error::SUCCESS;
    }

    SocketConnection *Server::accept(NWR &result, int &error) {
        auto addr_size = sizeof(addr);
        if ((error = ::accept(_socket, (sockaddr *) &addr, (socklen_t *) &addr_size)) < 0) [[unlikely]] {
            result = (NWR) Error::CONNECT_ACCEPT_ERROR;
            return nullptr;
        }

        result = (NWR) Error::SUCCESS;

        auto connection = new SocketConnection();
        connection->_socket = error;
        return connection;
    }
}