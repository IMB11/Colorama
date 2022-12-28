#pragma once

#include "Colorama.hpp"
#include "Coloring/MenuColorSwapper.hpp"

DECLARE_CLASS_CODEGEN(
    Colorama::UI, ConfigViewController, HMUI::ViewController,
    DECLARE_DEFAULT_CTOR();
    DECLARE_INSTANCE_FIELD_PRIVATE(Colorama::Coloring::MenuColorSwapper*,
                                   _menuColorSwapper);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, menuTab);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, energyTab);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, multiplierRingTab);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, progressBarTab);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, comboTab);
    DECLARE_INSTANCE_FIELD(HMUI::FlowCoordinator*, parentFlow);
    DECLARE_INJECT_METHOD(
        void, Construct,
        Colorama::Coloring::MenuColorSwapper* _menuColorSwapper);
    DECLARE_INSTANCE_METHOD(void, SwitchTab, int idx);
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate,
                                  &HMUI::ViewController::DidActivate,
                                  bool firstActivation, bool addedToHierarchy,
                                  bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidDeactivate,
                                  &HMUI::ViewController::DidDeactivate, bool removedFromHierarchy, bool screenSystemDisabling);)