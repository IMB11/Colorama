#pragma once

#include "Colorama.hpp"

#include "HMUI/FlowCoordinator.hpp"

#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSMLDataCache.hpp"

#include "UI/Views/InfoViewController.hpp"

#include "Coloring/Services/ColorizerService.hpp"

DECLARE_CLASS_CODEGEN(Colorama::UI, ColoramaFlowCoordinator, HMUI::FlowCoordinator,
                      DECLARE_PRIVATE_FIELD(GlobalNamespace::MainFlowCoordinator*, _mainFlowCoordinator);
                      DECLARE_PRIVATE_FIELD(InfoViewController*, _infoViewController);
                      DECLARE_INJECT_METHOD(void, Construct, GlobalNamespace::MainFlowCoordinator* mainFlowCoordinator, InfoViewController* infoViewController);
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