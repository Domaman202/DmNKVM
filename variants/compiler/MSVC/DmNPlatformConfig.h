#pragma once
#ifndef DMNKVM_DMNCONFIG_H
#define DMNKVM_DMNCONFIG_H

#define DMN_KVM_EXPORT __declspec(dllexport)
#define DMN_KVM_E(type, name) DMN_KVM_EXPORT type name
#define DMN_KVM_EE(name) DMN_KVM_E(enum, name)
#define DMN_KVM_ES(name) DMN_KVM_E(struct, name)
#define DMN_KVM_EC(name) DMN_KVM_E(class, name)

#endif /* DMNKVM_DMNCONFIG_H */
