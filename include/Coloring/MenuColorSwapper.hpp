#pragma once

#include "Colorama.hpp"
#include "GlobalNamespace/CampaignFlowCoordinator.hpp"
#include "GlobalNamespace/CenterStageScreenController.hpp"
#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "GlobalNamespace/MenuLightsManager.hpp"
#include "GlobalNamespace/MultiplayerModeSelectionFlowCoordinator.hpp"
#include "GlobalNamespace/PartyFreePlayFlowCoordinator.hpp"
#include "GlobalNamespace/SoloFreePlayFlowCoordinator.hpp"
#include "UnityEngine/SpriteRenderer.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

DECLARE_CLASS_CODEGEN_ZENJECT(
    Colorama::Coloring, MenuColorSwapper, Il2CppObject,
    DECLARE_DEFAULT_CTOR();
    DECLARE_INSTANCE_FIELD_PRIVATE(MenuLightsManager*, _menuLightsManager);
    DECLARE_INSTANCE_FIELD_PRIVATE(MainFlowCoordinator*, _mainFlowCoordinator);
    DECLARE_INSTANCE_FIELD_PRIVATE(CampaignFlowCoordinator*,
                                   _campaignFlowCoordinator);
    DECLARE_INSTANCE_FIELD_PRIVATE(CenterStageScreenController*,
                                   _centerStageScreenController);
    DECLARE_INSTANCE_FIELD_PRIVATE(SoloFreePlayFlowCoordinator*,
                                   _soloFreePlayFlowCoordinator);
    DECLARE_INSTANCE_FIELD_PRIVATE(PartyFreePlayFlowCoordinator*,
                                   _partyFreePlayFlowCoordinator);
    DECLARE_INSTANCE_FIELD_PRIVATE(SpriteRenderer*, _playersPlace);
    DECLARE_INSTANCE_FIELD_PRIVATE(MenuLightsPresetSO*, _defaultLightPreset);
    DECLARE_INSTANCE_FIELD_PRIVATE(MenuLightsPresetSO*,
                                   _defaultFailLightPreset);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize,
                                  &Zenject::IInitializable::Initialize);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &System::IDisposable::Dispose);
    DECLARE_INJECT_METHOD(
        void, Inject, MenuLightsManager* menuLightsManager,
        MainFlowCoordinator* mainFlowCoordinator,
        CampaignFlowCoordinator* campaignFlowCoordinator,
        SoloFreePlayFlowCoordinator* soloFreePlayFlowCoordinator,
        PartyFreePlayFlowCoordinator* partyFreePlayFlowCoordinator,
        CenterStageScreenController* centerStageScreenController);
    DECLARE_INSTANCE_METHOD(void, UpdateColors);
    DECLARE_INSTANCE_METHOD(void, PreviewColor, UnityEngine::Color color);
    )