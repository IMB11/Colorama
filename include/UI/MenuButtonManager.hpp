#pragma once

#include "Colorama.hpp"
#include "UI/ColoramaFlowCoordinator.hpp"

#include "HMUI/FlowCoordinator.hpp"
#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSMLDataCache.hpp"

DECLARE_CLASS_CODEGEN_ZENJECT(Colorama::UI, MenuButtonManager, Il2CppObject,
    DECLARE_INJECT_FIELD(GlobalNamespace::MainFlowCoordinator*, _mainFlowCoordinator);
    DECLARE_INJECT_FIELD(ColoramaFlowCoordinator*, _modFlowCoordinator);
    DECLARE_INSTANCE_FIELD(BSML::MenuButton*, _menuButton);
    DECLARE_CTOR(ctor);
    DECLARE_INSTANCE_METHOD(void, SummonModFlowCoordinator);
    DECLARE_OVERRIDE_METHOD(void, Initialize,
                            il2cpp_utils::il2cpp_type_check::MetadataGetter<
                                &::Zenject::IInitializable::Initialize>::get());
    DECLARE_OVERRIDE_METHOD(void, Dispose,
                            il2cpp_utils::il2cpp_type_check::MetadataGetter<
                                &::System::IDisposable::Dispose>::get());
)