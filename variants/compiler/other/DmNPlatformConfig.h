#pragma once
#ifndef DMNKVM_DMNCONFIG_H
#define DMNKVM_DMNCONFIG_H

#define DMN_KVM_E extern
#define DMN_KVM_ET(type, name) DMN_KVM_E type name
#define DMN_KVM_EE(name) enum name
#define DMN_KVM_ES(name) struct name
#define DMN_KVM_EC(name) class name

#endif /* DMNKVM_DMNCONFIG_H */
