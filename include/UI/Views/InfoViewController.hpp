#pragma once

#include "Colorama.hpp"

DECLARE_CLASS_CODEGEN(Colorama::UI, InfoViewController, HMUI::ViewController,
                      DECLARE_DEFAULT_CTOR();
                      DECLARE_OVERRIDE_METHOD_MATCH(
                          void, DidActivate, &HMUI::ViewController::DidActivate,
                          bool firstActivation, bool addedToHierarchy,
                          bool screenSystemEnabling);)