#pragma once

#include "Colorama.hpp"
#include "Coloring/MenuColorSwapper.hpp"
#include "UI/Views/InfoViewController.hpp"
#include "UI/Views/ConfigViewController.hpp"
#include "UI/Views/PreviewViewController.hpp"

#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "HMUI/FlowCoordinator.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSMLDataCache.hpp"

DECLARE_CLASS_CODEGEN(
    Colorama::UI, ColoramaFlowCoordinator, HMUI::FlowCoordinator,
    DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::MainFlowCoordinator*,
                          _mainFlowCoordinator);
    DECLARE_INSTANCE_FIELD_PRIVATE(InfoViewController*, _infoViewController);
    DECLARE_INSTANCE_FIELD_PRIVATE(PreviewViewController*, _previewViewController);
    DECLARE_INSTANCE_FIELD_PRIVATE(ConfigViewController*, _configViewController);
    DECLARE_INJECT_METHOD(
        void, Construct,
        GlobalNamespace::MainFlowCoordinator* mainFlowCoordinator,
        InfoViewController* infoViewController, ConfigViewController* configViewController, PreviewViewController* previewViewController);
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate,
                                  &HMUI::FlowCoordinator::DidActivate,
                                  bool firstActivation, bool addedToHierarchy,
                                  bool screenSystemEnabling);

    DECLARE_OVERRIDE_METHOD(
        void, BackButtonWasPressed,
        il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator",
                                       "BackButtonWasPressed", 1),
        HMUI::ViewController* topViewController);)