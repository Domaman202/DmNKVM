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
#ifdef DMN_KVM_PLATFORM_MINGW

    int inet_pton4(const char *src, char *dst) {
        uint8_t tmp[4], *tp;

        int saw_digit = 0;
        int octets = 0;
        *(tp = tmp) = 0;

        int ch;
        while ((ch = *src++) != '\0') {
            if (ch >= '0' && ch <= '9') {
                uint32_t n = *tp * 10 + (ch - '0');

                if (saw_digit && *tp == 0)
                    return 0;

                if (n > 255)
                    return 0;

                *tp = n;
                if (!saw_digit) {
                    if (++octets > 4)
                        return 0;
                    saw_digit = 1;
                }
            } else if (ch == '.' && saw_digit) {
                if (octets == 4)
                    return 0;
                *++tp = 0;
                saw_digit = 0;
            } else
                return 0;
        }
        if (octets < 4)
            return 0;

        memcpy(dst, tmp, 4);

        return 1;
    }

    int inet_pton6(const char *src, char *dst) {
        static const char xdigits[] = "0123456789abcdef";
        uint8_t tmp[16];

        auto tp = (uint8_t *) memset(tmp, '\0', 16);
        auto endp = tp + 16;
        uint8_t *colonp = nullptr;

        /* Leading :: requires some special handling. */
        if (*src == ':') {
            if (*++src != ':')
                return 0;
        }

        const char *curtok = src;
        int saw_xdigit = 0;
        uint32_t val = 0;
        int ch;
        while ((ch = tolower(*src++)) != '\0') {
            const char *pch = strchr(xdigits, ch);
            if (pch != nullptr) {
                val <<= 4;
                val |= (pch - xdigits);
                if (val > 0xffff)
                    return 0;
                saw_xdigit = 1;
                continue;
            }
            if (ch == ':') {
                curtok = src;
                if (!saw_xdigit) {
                    if (colonp)
                        return 0;
                    colonp = tp;
                    continue;
                } else if (*src == '\0') {
                    return 0;
                }
                if (tp + 2 > endp)
                    return 0;
                *tp++ = (uint8_t) (val >> 8) & 0xff;
                *tp++ = (uint8_t) val & 0xff;
                saw_xdigit = 0;
                val = 0;
                continue;
            }
            if (ch == '.' && ((tp + 4) <= endp) &&
                inet_pton4(curtok, (char *) tp) > 0) {
                tp += 4;
                saw_xdigit = 0;
                break; /* '\0' was seen by inet_pton4(). */
            }
            return 0;
        }
        if (saw_xdigit) {
            if (tp + 2 > endp)
                return 0;
            *tp++ = (uint8_t) (val >> 8) & 0xff;
            *tp++ = (uint8_t) val & 0xff;
        }
        if (colonp != nullptr) {
            /*
             * Since some memmove()'s erroneously fail to handle
             * overlapping regions, we'll do the shift by hand.
             */
            const int n = tp - colonp;

            if (tp == endp)
                return 0;

            for (int i = 1; i <= n; i++) {
                endp[-i] = colonp[n - i];
                colonp[n - i] = 0;
            }
            tp = endp;
        }
        if (tp != endp)
            return 0;

        memcpy(dst, tmp, 16);

        return 1;
    }

    int inet_pton(int af, const char *src, char *dst) {
        switch (af) {
            case AF_INET:
                return inet_pton4(src, dst);
            case AF_INET6:
                return inet_pton6(src, dst);
            default:
                return -1;
        }
    }

#endif /* DMN_KVM_PLATFORM_MINGW */

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
        NWR close() const {
#ifdef WIN32
            return closesocket(_socket) == SOCKET_ERROR ? NWR::CLOSE_SOCKET_ERROR : NWR::SUCCESS;
#else
            shutdown(_socket, 0);
            return ::close(_socket) == 0 ? NWR::SUCCESS : NWR::CLOSE_SOCKET_ERROR;
#endif /* WIN32 */
        }
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
        inline size_t sendBuf(void *buf, packet_size_t len) const {
            return send(_socket, DMN_KVM_NETWORK_CAST_TO_BUFFER(buf), len, 0);
        }

        /*!
         * Читает входящие в буфер
         * @param buf буфер в который нужно записать входящие данные
         * @param len размер данных которые нужно записать
         * @return TODO: ЯХЗ
         */
        inline size_t readBuf(void *buf, packet_size_t len) const {
            return recv(_socket, DMN_KVM_NETWORK_CAST_TO_BUFFER(buf), len, 0);
        }
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
        Client(const std::string &address, bool ipv6, uint16_t port, NWR &result, socket_t &error) {
            // Проверка на ipv6
            int ip_protocol = ipv6 ? AF_INET6 : AF_INET;

            // Создаём сокет
            if ((_socket = socket(ip_protocol, SOCK_STREAM, PF_UNSPEC)) < 0) [[unlikely]] {
                result = NWR::SOCKET_CREATE_ERROR;
                error = _socket;
                return;
            }

            // Выставляет сетевые параметры
            addr.sin_family = ip_protocol;
            addr.sin_port = port;
            if ((error = inet_pton(ip_protocol, address.c_str(), (char *) &(addr.sin_addr))) != 1) [[unlikely]] {
                result = NWR::IP_CONVERT_ERROR;
                return;
            }

            // Если мы ещё не померли, то возвращаем хороший результат
            result = NWR::SUCCESS;
            error = 0;
        }

/*!
         * Пытаемся подключится к серверу
         * @param error код ошибки (!LOW LEVEL!)
         * @return Результат выполнения
         */
        NWR tryConnect(socket_t &error) {
            if (connect(_socket, (sockaddr *) &addr, sizeof(addr)) < 0) [[unlikely]]
                return NWR::CONNECT_ERROR;
            return NWR::SUCCESS;
        }
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
        Server(uint16_t port, NWR &result, socket_t &error) {
            // Создаём сокет
            if ((_socket = socket(AF_INET, SOCK_STREAM, PF_UNSPEC)) < 0) [[unlikely]] {
                result = NWR::SOCKET_CREATE_ERROR;
                error = _socket;
                return;
            }

            // Выставляет сетевые параметры
            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = INADDR_ANY;
            addr.sin_port = port;

            // Биндим сокет
            if ((error = bind(_socket, (sockaddr *) &addr, sizeof(addr))) < 0) [[unlikely]] {
                result = NWR::SOCKET_BIND_ERROR;
                return;
            }

            result = NWR::SUCCESS;
        }

        /*!
         * Конструктор сервера
         * @param address адрес клиента
         * @param ipv6 это IPv6 адрес?
         * @param port порт
         * @param result результат
         * @param error код ошибки (!LOW LEVEL!)
         */
        Server(const std::string &address, bool ipv6, uint16_t port, NWR &result, socket_t &error) {
            // Проверка на ipv6
            int ip_protocol = ipv6 ? AF_INET6 : AF_INET;

            // Создаём сокет
            if ((_socket = socket(ip_protocol, SOCK_STREAM, PF_UNSPEC)) < 0) [[unlikely]] {
                result = NWR::SOCKET_CREATE_ERROR;
                error = _socket;
                return;
            }

            // Выставляет сетевые параметры
            addr.sin_family = ip_protocol;
            addr.sin_port = port;
            if ((error = inet_pton(ip_protocol, address.c_str(), (char *) &(addr.sin_addr))) != 1) [[unlikely]] {
                result = NWR::IP_CONVERT_ERROR;
                return;
            }

            // Биндим сокет
            if ((error = bind(_socket, (sockaddr *) &addr, sizeof(addr))) < 0) [[unlikely]] {
                result = NWR::SOCKET_BIND_ERROR;
                return;
            }

            // Если всё зашибись, то выставляем соответствующий результат
            result = NWR::SUCCESS;
        }

        /*!
         * Разрешаем подключение для n-го кол-во клиентов
         * @param i кол-во клиентов которые могут подключиться
         * @param error кол ошибки (!LOW LEVEL!)
         * @return Результат
         */
        NWR listen(int i, socket_t &error) {
            if ((error = ::listen(_socket, i)) < 0) [[unlikely]]
                return NWR::LISTEN_ERROR;
            return NWR::SUCCESS;
        }

        /*!
         * Принимаем соединение
         * @param result результат
         * @param error код ошибки (LOW LEVEL)
         * @return Объект описывающий соединение
         */
        SocketConnection *accept(NWR &result, socket_t &error) {
            auto addr_size = sizeof(addr);
#ifdef WIN32
            if ((error = ::accept(_socket, (sockaddr *) &addr, (int *) &addr_size)) < 0) [[unlikely]] {
                result = NWR::CONNECT_ACCEPT_ERROR;
                return nullptr;
            }
#else
            if ((error = ::accept(_socket, (sockaddr *) &addr, (socklen_t *) &addr_size)) < 0) [[unlikely]] {
                result = NWR::CONNECT_ACCEPT_ERROR;
                return nullptr;
            }
#endif /* WIN32 */

            result = NWR::SUCCESS;

            auto connection = new SocketConnection();
            connection->_socket = error;
            return connection;
        }
    };
}

#endif //DMN_KVM_NETWORK_HPP