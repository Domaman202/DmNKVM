#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_ERROR_HPP
#define DMN_KVM_ERROR_HPP

namespace DmN::KVM::ERROR {
    /// (Collect Result) Результат сборки памяти
    DMN_KVM_E enum CR {
        /// Память освобождена успешно
        SUCCESS = 0,
        /// Объект нельзя собрать
        OBJECT_NO_COLLECTABLE = 1,
        /// На объект ещё есть ссылки
        OBJECT_REFERENCE_NOT_NULL = 2
    };
}


#endif /* DMN_KVM_ERROR_HPP */