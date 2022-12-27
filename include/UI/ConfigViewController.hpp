#pragma once

#include "Colorama.hpp"

#include "Coloring/Services/ColorizerService.hpp"
#include "Coloring/Services/DefaultMenuService.hpp"

#include "UI/ColoramaFlowCoordinator.hpp"

DECLARE_CLASS_CODEGEN_ZENJECT(Colorama::UI, ConfigViewController, HMUI::ViewController,
                              DECLARE_INJECT_FIELD(Colorama::Coloring::Services::DefaultMenuService*, _defaultMenuService);
                              DECLARE_INJECT_FIELD(Colorama::UI::ColoramaFlowCoordinator*, _parentFlowCoordinator);
                              DECLARE_DEFAULT_CTOR();
                              DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate,
                                                            &HMUI::ViewController::DidActivate,
                                                            bool firstActivation, bool addedToHierarchy,
                                                            bool screenSystemEnabling);
)