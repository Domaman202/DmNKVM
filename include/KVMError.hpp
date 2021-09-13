#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_ERROR_HPP
#define DMN_KVM_ERROR_HPP

#include "KVMConfig.hpp"

namespace DmN {
    namespace KVM {
        namespace Error {
            /// Основа для ошибок
            DMN_KVM_E enum BaseError {
                /// Операция выполнена успешно
                SUCCESS = 0,
                /// Операция сдохла, но никто не знает почему
                UNKNOWN_ERROR = 1,
            };

            /// (Collect Result) Результат сборки памяти
            DMN_KVM_E enum CR {
                /// Объект нельзя собрать
                OBJECT_NO_COLLECTABLE = 2,
                /// На объект ещё есть ссылки
                OBJECT_REFERENCE_NOT_NULL = 3
            };

            /// (Network Work Result) Результат запуска клиента
            DMN_KVM_E enum NWR {
                /// Что-то пошло по сами знаете чему и объект не смог запустить сокет
                SOCKET_CREATE_ERROR = 2,
                /// Не удалось конвертировать IP
                IP_CONVERT_ERROR = 3,
                /// Ошибка подключения
                CONNECT_ERROR = 4,
                /// Ошибка бинда сокета
                SOCKET_BIND_ERROR = 5,
                /// Ошибка принятия соединения
                CONNECT_ACCEPT_ERROR = 6,
                /// Ошибка просмотра соединений
                LISTEN_ERROR = 7
            };
        }
    }
}


#endif /* DMN_KVM_ERROR_HPP */