#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "Zenject/IInitializable.hpp"
#include "System/IDisposable.hpp"

#define ZENJECT_INTERFACES \
  { classof(::Zenject::IInitializable *), classof(::System::IDisposable *) }

#define DECLARE_CLASS_CODEGEN_ZENJECT(namespaze, klassname, baseT, ...) \
___DECLARE_TYPE_WRAPPER_INHERITANCE( \
namespaze, klassname, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, \
    baseT, #namespaze, ZENJECT_INTERFACES, \
    0, nullptr,                                                         \
    __VA_ARGS__\
)