#pragma once

#include "Colorama.hpp"

#include "UnityEngine/MonoBehaviour.hpp"

#include "GlobalNamespace/ComboUIController.hpp"

DECLARE_CLASS_CODEGEN(Colorama::Coloring, ComboModifierHelper, UnityEngine::MonoBehaviour,
                              DECLARE_INSTANCE_FIELD(GlobalNamespace::ComboUIController*, _comboUIController);
                              DECLARE_INSTANCE_METHOD(void, OnDestroy);
                              DECLARE_INJECT_METHOD(void, HelperSetup, GlobalNamespace::ComboUIController* comboUIController);
                              DECLARE_INSTANCE_METHOD(void, ModPanel);
                              DECLARE_DEFAULT_CTOR();
)