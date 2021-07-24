#pragma once
#ifndef DMNKVM_KVMERROR_HPP
#define DMNKVM_KVMERROR_HPP

namespace DmN::KVM::ERROR {
    /// Результат сборки памяти
    enum Collect_Result {
        /// Память освобождена успешно
        SUCCESS = 0,
        /// Объект нельзя собрать
        OBJECT_NO_COLLECTABLE = 1,
        /// На объект ещё есть ссылки
        OBJECT_REFERENCE_NOT_NULL = 2
    };
}


#endif /* DMNKVM_KVMERROR_HPP */