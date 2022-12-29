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

void MenuColorSwapper::Dispose() {
  // ... utterly useless.
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
#define resetPreset(val) val = this->_defaultLightPreset

  MenuConfiguration configuration = getColoramaConfig().menuConfiguration.GetValue();

  _playersPlace->set_color(
      configuration.feetColor.enabled
          ? ColorPair::convert(configuration.feetColor)
          : _playersPlace->get_color());

  if (configuration.freeplayLighting.enabled) {
	auto lights = Utils::createMenuLights(this->_defaultLightPreset, ColorPair::convert(configuration.freeplayLighting));
	this->_soloFreePlayFlowCoordinator->defaultLightsPreset = lights;
	this->_partyFreePlayFlowCoordinator->defaultLightsPreset = lights;
  } else {
	resetPreset(this->_soloFreePlayFlowCoordinator->defaultLightsPreset);
	resetPreset(this->_partyFreePlayFlowCoordinator->defaultLightsPreset);
  }

  if (configuration.resultsLighting.enabled) {
	auto lights = Utils::createMenuLights(this->_defaultLightPreset, ColorPair::convert(configuration.resultsLighting));
	this->_soloFreePlayFlowCoordinator->resultsClearedLightsPreset = lights;
	this->_campaignFlowCoordinator->resultsClearedLightsPreset = lights;
	this->_partyFreePlayFlowCoordinator->resultsClearedLightsPreset = lights;
  } else {
	resetPreset(this->_soloFreePlayFlowCoordinator->resultsClearedLightsPreset);
	resetPreset(
	    this->_partyFreePlayFlowCoordinator->resultsClearedLightsPreset);
	resetPreset(this->_campaignFlowCoordinator->resultsClearedLightsPreset);
  }

  if (configuration.resultsFailLighting.enabled) {
	auto lights = Utils::createMenuLights(
	    this->_defaultLightPreset, ColorPair::convert(configuration.resultsFailLighting));
	this->_soloFreePlayFlowCoordinator->resultsFailedLightsPreset = lights;
	this->_partyFreePlayFlowCoordinator->resultsClearedLightsPreset = lights;
  } else {
	this->_soloFreePlayFlowCoordinator->resultsFailedLightsPreset =
	    this->_defaultFailLightPreset;
	this->_partyFreePlayFlowCoordinator->resultsFailedLightsPreset =
	    this->_defaultFailLightPreset;
  }

  if (configuration.campaignLighting.enabled) {
	auto lights = Utils::createMenuLights(
	    this->_defaultLightPreset, ColorPair::convert(configuration.campaignLighting));
	this->_campaignFlowCoordinator->defaultLightsPreset = lights;
  } else {
	resetPreset(this->_campaignFlowCoordinator->defaultLightsPreset);
  }

  if (configuration.multiplayerIdleColor.enabled) {
	auto lights = Utils::createMenuLights(
	    this->_defaultLightPreset, ColorPair::convert(configuration.multiplayerIdleColor));
	this->_centerStageScreenController->lobbyLightsPreset = lights;
  } else {
	resetPreset(this->_centerStageScreenController->lobbyLightsPreset);
  }

  if (configuration.multiplayerCountdownColor.enabled) {
	auto lights = Utils::createMenuLights(
	    this->_defaultLightPreset,
	    ColorPair::convert(configuration.multiplayerCountdownColor));
	this->_centerStageScreenController->countdownMenuLightsPreset = lights;
  } else {
	resetPreset(this->_centerStageScreenController->countdownMenuLightsPreset);
  }

  if (configuration.gamemodeLighting.enabled) {
	auto lights = Utils::createMenuLights(this->_defaultLightPreset, ColorPair::convert(configuration.gamemodeLighting));
	this->_mainFlowCoordinator->defaultLightsPreset = lights;
  } else {
	resetPreset(this->_mainFlowCoordinator->defaultLightsPreset);
  }

#undef config
#undef resetPreset
}