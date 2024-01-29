#pragma once

#include "Colorama.hpp"
#include "custom-types/shared/delegate.hpp"

// clang-format off
DECLARE_CLASS_CODEGEN(Colorama::UI, CViewController, HMUI::ViewController,
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    DECLARE_INSTANCE_FIELD(HMUI::FlowCoordinator*, flowCoordinator);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, menuColorsButton);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, atmosphereButton);

public:
    // Credits AnyTweaks - amazing UI layout.
    UnityEngine::UI::Button* CreateUIViewControllerButton(UnityEngine::Transform* parent, const std::string& title, std::string description, HMUI::ViewController* viewController) const;
)
// clang-format on