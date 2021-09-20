#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_PROCESS_H
#define DMN_KVM_PROCESS_H

#include "KVMThrowable.hpp"
#include "KVMNetwork.hpp"
#include "KVMThread.hpp"
#include "KVMHeap.hpp"

namespace DmN::KVM {
    class Process {
        /// Массив потоков
        Thread **threads = nullptr;
        /// Кол-во потоков
        uint8_t tc = 0;
        /// Куча
        Heap *heap = nullptr;
        /// Хендлер сети
        Network::NetworkHandler* network = nullptr;
        /// Ошибка
        Throwable *error = nullptr;
    };
}

#endif /* DMN_KVM_PROCESS_H */