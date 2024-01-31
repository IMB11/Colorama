#pragma once

#include "Colorama.hpp"
#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "HMUI/FlowCoordinator.hpp"
#include "UI/ColoramaFlowCoordinator.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSMLDataCache.hpp"

DECLARE_CLASS_CODEGEN_ZENJECT(
    Colorama::UI, MenuButtonManager, Il2CppObject,
    DECLARE_INSTANCE_FIELD(GlobalNamespace::MainFlowCoordinator*,
                           _mainFlowCoordinator);
    DECLARE_INSTANCE_FIELD(ColoramaFlowCoordinator*, _modFlowCoordinator);
    DECLARE_CTOR(ctor,
                          GlobalNamespace::MainFlowCoordinator* mainfc,
                          ColoramaFlowCoordinator* modfc, InfoViewController *infoViewController, ConfigViewController *configViewController, PreviewViewController* previewViewController);
    DECLARE_INSTANCE_FIELD(BSML::MenuButton*, _menuButton);
    DECLARE_INSTANCE_METHOD(void, SummonModFlowCoordinator);
    DECLARE_OVERRIDE_METHOD(void, Initialize,
                            il2cpp_utils::il2cpp_type_check::MetadataGetter<
                                &::Zenject::IInitializable::Initialize>::get());
    DECLARE_OVERRIDE_METHOD(void, Dispose,
                            il2cpp_utils::il2cpp_type_check::MetadataGetter<
                                &::System::IDisposable::Dispose>::get());)