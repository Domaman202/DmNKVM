#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_ERROR_HPP
#define DMN_KVM_ERROR_HPP

namespace DmN::KVM::Error {
    /// Основа для ошибок
    enum class BaseError {
        /// Операция выполнена успешно
        SUCCESS = 0,
        /// Операция сдохла, но никто не знает почему
        UNKNOWN_ERROR = 1,
    };

    /// (Collect Result) Результат сборки памяти
    enum class CR {
        /// Операция выполнена успешно
        SUCCESS = 0,
        /// Операция сдохла, но никто не знает почему
        UNKNOWN_ERROR = 1,
        /// Объект нельзя собрать
        OBJECT_NO_COLLECTABLE = 2,
        /// На объект ещё есть ссылки
        OBJECT_REFERENCE_NOT_NULL = 3
    };

    /// (Network Work Result) Результат сетевой
    enum class NWR {
        /// Операция выполнена успешно
        SUCCESS = 0,
        /// Операция сдохла, но никто не знает почему
        UNKNOWN_ERROR = 1,
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
        LISTEN_ERROR = 7,
        // Ошибка закрытия сокета
        CLOSE_SOCKET_ERROR = 8
    };
}

#endif /* DMN_KVM_ERROR_HPP */