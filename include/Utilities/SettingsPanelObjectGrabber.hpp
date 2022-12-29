#pragma once

#include "Colorama.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/coroutine.hpp"

DECLARE_CLASS_CODEGEN(
    Colorama::Utilities, SettingsPanelObjectGrabber, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(bool, isCompleted);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, multiplierPanel);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, energyPanel);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, comboPanel);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, progressPanel);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, immediateRankPanel);
    DECLARE_INSTANCE_METHOD(UnityEngine::GameObject*, FinalizePanel, UnityEngine::MonoBehaviour* controller);
    DECLARE_INSTANCE_METHOD(void, Start);
    public:
    	custom_types::Helpers::Coroutine GrabPanels();
    )