#pragma once
#ifndef DMNKVM_DMNCONFIG_H
#define DMNKVM_DMNCONFIG_H

#ifndef DMN_KVM_EXPORT
#define DMN_KVM_E __declspec(dllexport)
#elif
#define DMN_KVM_E __declspec(dllimport)
#endif

#define DMN_KVM_ET(type, name) DMN_KVM_EXPORT type name
#define DMN_KVM_EE(name) DMN_KVM_E(enum, name)
#define DMN_KVM_ES(name) DMN_KVM_E(struct, name)
#define DMN_KVM_EC(name) DMN_KVM_E(class, name)

#endif /* DMNKVM_DMNCONFIG_H */
