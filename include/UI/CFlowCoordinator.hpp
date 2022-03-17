#pragma once

#include "Colorama.hpp"
#include "UI/CViewController.hpp"

// clang-format off
DECLARE_CLASS_CODEGEN(Colorama::UI, CFlowCoordinator, HMUI::FlowCoordinator,
    DECLARE_INSTANCE_FIELD(CViewController*, cViewController);
    DECLARE_INSTANCE_FIELD(HMUI::ViewController*, currentViewController);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, BackButtonWasPressed, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "BackButtonWasPressed", 1), HMUI::ViewController* topViewController);
)
// clang-format on