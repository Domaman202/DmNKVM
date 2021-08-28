#pragma once
#ifndef DMNKVM_DMNCONFIG_H
#define DMNKVM_DMNCONFIG_H

#ifndef DMN_KVM_EXPORT
#define DMN_KVM_E __declspec(dllexport)
#elif
#define DMN_KVM_E __declspec(dllimport)
#endif

#define DMN_KVM_EE extern
#define DMN_KVM_EF DMN_KVM_EE DMN_KVM_EE

#endif /* DMNKVM_DMNCONFIG_H */
