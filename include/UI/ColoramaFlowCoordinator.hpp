#pragma once

#include "Colorama.hpp"

#include "HMUI/FlowCoordinator.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

DECLARE_CLASS_CODEGEN(
    Colorama::UI, ColoramaFlowCoordinator, HMUI::FlowCoordinator,
    DECLARE_INSTANCE_FIELD(HMUI::ViewController *, currentViewController);

    DECLARE_INSTANCE_METHOD(void, PreviewColor, UnityEngine::Color colorToChangeTo);

    DECLARE_OVERRIDE_METHOD_MATCH(void, Update, &UnityEngine::MonoBehaviour::Update)

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