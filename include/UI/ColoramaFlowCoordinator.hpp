#pragma once

#include "Colorama.hpp"

#include "HMUI/FlowCoordinator.hpp"

#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSMLDataCache.hpp"

#include "Coloring/Services/ColorizerService.hpp"
#include "UI/Views/ConfigViewController.hpp"

DECLARE_CLASS_CODEGEN_ZENJECT(Colorama::UI, ColoramaFlowCoordinator, HMUI::FlowCoordinator,
    DECLARE_INJECT_FIELD(
        ListWrapper<Colorama::Coloring::Services::ColorizerService *>,
        _colorizerServices);
    DECLARE_INSTANCE_FIELD(Colorama::UI::ConfigViewController*, _configViewController);
    DECLARE_INJECT_METHOD(void, Inject, ListWrapper<Colorama::Coloring::Services::ColorizerService *> _colorizerServices);
    DECLARE_OVERRIDE_METHOD(void, Initialize,
                            il2cpp_utils::il2cpp_type_check::MetadataGetter<
                                &::Zenject::IInitializable::Initialize>::get());
    DECLARE_OVERRIDE_METHOD(void, Dispose,
                            il2cpp_utils::il2cpp_type_check::MetadataGetter<
                                &::System::IDisposable::Dispose>::get());
    //    DECLARE_DEFAULT_CTOR();
    //    DECLARE_INSTANCE_METHOD(void, PreviewColor, UnityEngine::Color
    //    colorToChangeTo);
    //
    //    DECLARE_OVERRIDE_METHOD_MATCH(void, Update,
    //    &UnityEngine::MonoBehaviour::Update)
    //
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate,
                                  &HMUI::FlowCoordinator::DidActivate,
                                  bool firstActivation, bool addedToHierarchy,
                                  bool screenSystemEnabling);

    DECLARE_OVERRIDE_METHOD(
        void, BackButtonWasPressed,
        il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator",
                                       "BackButtonWasPressed", 1),
        HMUI::ViewController *topViewController);
)