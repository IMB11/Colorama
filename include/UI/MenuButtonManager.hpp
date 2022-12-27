#pragma once

#include "Colorama.hpp"
#include "UI/ColoramaFlowCoordinator.hpp"

#include "HMUI/FlowCoordinator.hpp"
#include "System/IDisposable.hpp"
#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "Zenject/IInitializable.hpp"

#include "lapiz/shared/macros.hpp"

#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSMLDataCache.hpp"

#define MenuButtonManager_INTERFACES                                     \
  { classof(::Zenject::IInitializable *), classof(::System::IDisposable *) }

___DECLARE_TYPE_WRAPPER_INHERITANCE(
    Colorama::UI, MenuButtonManager, Il2CppTypeEnum::IL2CPP_TYPE_CLASS,
    Il2CppObject, "Colorama::UI", MenuButtonManager_INTERFACES ,
    0, nullptr,
    DECLARE_INSTANCE_FIELD(GlobalNamespace::MainFlowCoordinator*, _mainFlowCoordinator);
    DECLARE_INSTANCE_FIELD(ColoramaFlowCoordinator*, _modFlowCoordinator);
    DECLARE_INSTANCE_FIELD(BSML::MenuButton*, _menuButton);
    DECLARE_CTOR(ctor, GlobalNamespace::MainFlowCoordinator* mfc, ColoramaFlowCoordinator* mofc);
//    DECLARE_INJECT_METHOD(void, Inject, GlobalNamespace::MainFlowCoordinator* mfc, ColoramaFlowCoordinator* mofc);
    DECLARE_INSTANCE_METHOD(void, SummonModFlowCoordinator);
    DECLARE_OVERRIDE_METHOD(void, Initialize,
                            il2cpp_utils::il2cpp_type_check::MetadataGetter<
                                &::Zenject::IInitializable::Initialize>::get());
    DECLARE_OVERRIDE_METHOD(void, Dispose,
                            il2cpp_utils::il2cpp_type_check::MetadataGetter<
                                &::System::IDisposable::Dispose>::get());
)