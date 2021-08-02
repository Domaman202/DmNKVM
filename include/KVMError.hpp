#pragma once
#ifndef DMNKVM_KVMERROR_HPP
#define DMNKVM_KVMERROR_HPP

namespace DmN::KVM::ERROR {
    /// (Collect Result) Результат сборки памяти
    DMN_KVM_EE(CR) {
        /// Память освобождена успешно
        SUCCESS = 0,
        /// Объект нельзя собрать
        OBJECT_NO_COLLECTABLE = 1,
        /// На объект ещё есть ссылки
        OBJECT_REFERENCE_NOT_NULL = 2
    };
}


#endif /* DMNKVM_KVMERROR_HPP */