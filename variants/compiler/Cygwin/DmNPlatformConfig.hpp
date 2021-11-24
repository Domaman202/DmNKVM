#pragma once
#ifndef DMN_KVM_PLATFORM_CONFIG_H
#define DMN_KVM_PLATFORM_CONFIG_H

#include <typeinfo.h>

#define DMN_KVM_PLATFORM_CYGWIN

#define DMN_KVM_RS(a,b,c) (*regs)[RNV(a, b)] = c

#endif /* DMN_KVM_PLATFORM_CONFIG_H */