#pragma once
#ifndef DMN_KVM_PLATFORM_CONFIG_H
#define DMN_KVM_PLATFORM_CONFIG_H

#include <typeinfo>

#define DMN_KVM_PLATFORM_MINGW

#define DMN_KVM_RS(a,b,c) auto x = c; regs->rs[RNV(a, b)] = x

#endif /* DMN_KVM_PLATFORM_CONFIG_H */