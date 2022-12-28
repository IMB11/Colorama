#include "Coloring/MenuColorSwapper.hpp"

#include "Coloring/ColorUtils.hpp"
#include "UnityEngine/GameObject.hpp"

DEFINE_TYPE(Colorama::Coloring, MenuColorSwapper)

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace Colorama::Coloring;

void MenuColorSwapper::Inject(
    MenuLightsManager *menuLightsManager,
    MainFlowCoordinator *mainFlowCoordinator,
    CampaignFlowCoordinator *campaignFlowCoordinator,
    SoloFreePlayFlowCoordinator *soloFreePlayFlowCoordinator,
    PartyFreePlayFlowCoordinator *partyFreePlayFlowCoordinator,
    CenterStageScreenController *centerStageScreenController) {
  this->_menuLightsManager = menuLightsManager;
  this->_mainFlowCoordinator = mainFlowCoordinator;
  this->_campaignFlowCoordinator = campaignFlowCoordinator;
  this->_soloFreePlayFlowCoordinator = soloFreePlayFlowCoordinator;
  this->_partyFreePlayFlowCoordinator = partyFreePlayFlowCoordinator;
  this->_centerStageScreenController = centerStageScreenController;
}

void MenuColorSwapper::Initialize() {
  this->_defaultLightPreset = this->_menuLightsManager->defaultPreset;
  this->_defaultFailLightPreset =
      this->_soloFreePlayFlowCoordinator->resultsFailedLightsPreset;

  auto playersPlace = GameObject::Find("PlayersPlace");
  this->_playersPlace =
      playersPlace->GetComponentInChildren<SpriteRenderer *>();
  UpdateColors();
}

void MenuColorSwapper::PreviewColor(UnityEngine::Color color) {
  this->_menuLightsManager->SetColorPreset(Utils::createMenuLights(this->_defaultLightPreset, color), true);
}

void MenuColorSwapper::UpdateColors() {
#define config getColoramaConfig()
#define resetPreset(val) val = this->_defaultLightPreset
  _playersPlace->set_color(
      config.Can_Menu_FeetColor.GetValue()
          ? config.Menu_FeetColor.GetValue().operator UnityEngine::Color()
          : _playersPlace->get_color());

  if (config.Can_Menu_FreeplayColor.GetValue()) {
	auto lights = Utils::createMenuLights(this->_defaultLightPreset,
	                                      config.Menu_FreeplayColor.GetValue());
	this->_soloFreePlayFlowCoordinator->defaultLightsPreset = lights;
	this->_partyFreePlayFlowCoordinator->defaultLightsPreset = lights;
  } else {
	resetPreset(this->_soloFreePlayFlowCoordinator->defaultLightsPreset);
	resetPreset(this->_partyFreePlayFlowCoordinator->defaultLightsPreset);
  }

  if (config.Can_Menu_ResultsColor.GetValue()) {
	auto lights = Utils::createMenuLights(this->_defaultLightPreset,
	                                      config.Menu_ResultsColor.GetValue());
	this->_soloFreePlayFlowCoordinator->resultsClearedLightsPreset = lights;
	this->_campaignFlowCoordinator->resultsClearedLightsPreset = lights;
	this->_partyFreePlayFlowCoordinator->resultsClearedLightsPreset = lights;
  } else {
	resetPreset(this->_soloFreePlayFlowCoordinator->resultsClearedLightsPreset);
	resetPreset(
	    this->_partyFreePlayFlowCoordinator->resultsClearedLightsPreset);
	resetPreset(this->_campaignFlowCoordinator->resultsClearedLightsPreset);
  }

  if (config.Can_Menu_ResultsFailColor.GetValue()) {
	auto lights = Utils::createMenuLights(
	    this->_defaultLightPreset, config.Menu_ResultsFailColor.GetValue());
	this->_soloFreePlayFlowCoordinator->resultsFailedLightsPreset = lights;
	this->_partyFreePlayFlowCoordinator->resultsClearedLightsPreset = lights;
  } else {
	this->_soloFreePlayFlowCoordinator->resultsFailedLightsPreset =
	    this->_defaultFailLightPreset;
	this->_partyFreePlayFlowCoordinator->resultsFailedLightsPreset =
	    this->_defaultFailLightPreset;
  }

  if (config.Can_Menu_CampaignsColor.GetValue()) {
	auto lights = Utils::createMenuLights(
	    this->_defaultLightPreset, config.Menu_CampaignsColor.GetValue());
	this->_campaignFlowCoordinator->defaultLightsPreset = lights;
  } else {
	resetPreset(this->_campaignFlowCoordinator->defaultLightsPreset);
  }

  if (config.Can_Menu_MultiplayerColor.GetValue()) {
	auto lights = Utils::createMenuLights(
	    this->_defaultLightPreset, config.Menu_MultiplayerColor.GetValue());
	this->_centerStageScreenController->lobbyLightsPreset = lights;
  } else {
	resetPreset(this->_centerStageScreenController->lobbyLightsPreset);
  }

  if (config.Can_Menu_MultiplayerCountdownColor.GetValue()) {
	auto lights = Utils::createMenuLights(
	    this->_defaultLightPreset,
	    config.Menu_MultiplayerCountdownColor.GetValue());
	this->_centerStageScreenController->countdownMenuLightsPreset = lights;
  } else {
	resetPreset(this->_centerStageScreenController->countdownMenuLightsPreset);
  }

  if (config.Can_Menu_GamemodeColor.GetValue()) {
	auto lights = Utils::createMenuLights(this->_defaultLightPreset,
	                                      config.Menu_GamemodeColor.GetValue());
	this->_mainFlowCoordinator->defaultLightsPreset = lights;
  } else {
	resetPreset(this->_mainFlowCoordinator->defaultLightsPreset);
  }

#undef config
#undef resetPreset
}