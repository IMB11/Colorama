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
    DECLARE_PRIVATE_FIELD(MenuLightsManager*, _menuLightsManager);
    DECLARE_PRIVATE_FIELD(MainFlowCoordinator*, _mainFlowCoordinator);
    DECLARE_PRIVATE_FIELD(CampaignFlowCoordinator*,
                                   _campaignFlowCoordinator);
    DECLARE_PRIVATE_FIELD(CenterStageScreenController*,
                                   _centerStageScreenController);
    DECLARE_PRIVATE_FIELD(SoloFreePlayFlowCoordinator*,
                                   _soloFreePlayFlowCoordinator);
    DECLARE_PRIVATE_FIELD(PartyFreePlayFlowCoordinator*,
                                   _partyFreePlayFlowCoordinator);
    DECLARE_PRIVATE_FIELD(SpriteRenderer*, _playersPlace);
    DECLARE_PRIVATE_FIELD(MenuLightsPresetSO*, _defaultLightPreset);
    DECLARE_PRIVATE_FIELD(MenuLightsPresetSO*,
                                   _defaultFailLightPreset);
    DECLARE_OVERRIDE_METHOD(void, Initialize, GET_ZENJECT_METHOD(Zenject::IInitializable::Initialize));
    DECLARE_OVERRIDE_METHOD(void, Dispose, GET_ZENJECT_METHOD(System::IDisposable::Dispose));
    DECLARE_CTOR(ctor, MenuLightsManager* menuLightsManager,
        MainFlowCoordinator* mainFlowCoordinator,
        CampaignFlowCoordinator* campaignFlowCoordinator,
        SoloFreePlayFlowCoordinator* soloFreePlayFlowCoordinator,
        PartyFreePlayFlowCoordinator* partyFreePlayFlowCoordinator,
        CenterStageScreenController* centerStageScreenController);
    DECLARE_INSTANCE_METHOD(void, UpdateColors);
    DECLARE_INSTANCE_METHOD(void, PreviewColor, UnityEngine::Color color);
    )