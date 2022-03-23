#pragma once

#include "Colorama.hpp"

// clang-format off
DECLARE_CLASS_CODEGEN(Colorama::UI, AtmosphereViewController, HMUI::ViewController,
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_INSTANCE_FIELD(HMUI::FlowCoordinator*, parentFlowCoordinator);
)
// clang-format on