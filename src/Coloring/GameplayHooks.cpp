#include <GlobalNamespace/GameEnergyUIPanel.hpp>

#include "Colorama.hpp"
#include "GlobalNamespace/ComboUIController.hpp"
#include "GlobalNamespace/GameEnergyUIPanel.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"
#include "GlobalNamespace/IGameEnergyCounter.hpp"
#include "HMUI/ImageView.hpp"
#include "UnityEngine/Time.hpp"
#include "UnityEngine/Transform.hpp"

using namespace UnityEngine;
using namespace HMUI;
using namespace GlobalNamespace;

MAKE_HOOK_MATCH(ComboUIController_StartHook, &ComboUIController::Start, void, ComboUIController* self) {
  ComboUIController_StartHook(self);

  ComboConfiguration config = getColoramaConfig().comboConfiguration.GetValue();
  if(self->get_isActiveAndEnabled() && config.enabled) {
    auto fullComboLines = self->GetComponentsInChildren<ImageView*>();

    if(config.useGradient) {
      fullComboLines[0]->gradient = true;
      fullComboLines[0]->set_color(Color::get_white());
      fullComboLines[1]->gradient = true;
      fullComboLines[1]->set_color(Color::get_white());

      fullComboLines[0]->color0 = config.topLeft;
      fullComboLines[0]->color1 = config.topRight;

      if(config.mirrorToBottom) {
        fullComboLines[1]->color0 = config.topLeft;
        fullComboLines[1]->color1 = config.topRight;
      } else {
        fullComboLines[1]->color0 = config.bottomLeft;
        fullComboLines[1]->color1 = config.bottomRight;
      }
    } else {
      fullComboLines[0]->gradient = false;
      fullComboLines[1]->gradient = false;
      fullComboLines[0]->set_color(config.topLineColor);
      fullComboLines[1]->set_color(config.bottomLineColor);
    }
  }
}

namespace GameplayUtils {
float repeat(float t, float length = 1.0F) {
  return std::clamp(t - std::floor(t / length) * length, 0.0f, length);
}

float pingPong(float t, float length = 1.0F) {
  t = repeat(t, length * 2.0F);
  return length - std::abs(t - length);
}
}

MAKE_HOOK_MATCH(GameEnergyUIPanel_RefreshHook, &GameEnergyUIPanel::RefreshEnergyUI, void, GameEnergyUIPanel* self, float energy) {
  GameEnergyUIPanel_RefreshHook(self, energy);

  EnergyBarConfiguration config = getColoramaConfig().energyBarConfiguration.GetValue();

  GameplayModifiers::EnergyType modifierType = self->gameEnergyCounter->get_energyType();



  if(modifierType == GameplayModifiers::EnergyType::Battery) {
    ListW<UnityEngine::UI::Image*> segments = self->batteryLifeSegments;
    segments[0]->set_color(config.lowColor);
    segments[1]->set_color(Color::Lerp(config.lowColor, config.midColor, 0.34F));
    segments[2]->set_color(Color::Lerp(config.midColor, config.highColor, 0.66F));
    segments[3]->set_color(config.highColor);
    return;
  }

  UI::Image* mainImage = self->energyBar;
  if(modifierType == GameplayModifiers::EnergyType::Battery) {
    if(self->gameEnergyCounter->get_instaFail()) {
      mainImage->set_color(config.highColor);
    } else {
      mainImage->set_color(config.midColor);
    }
  }

    if(config.rainbowFull && (self->gameEnergyCounter->get_instaFail() || energy == 1.0F || modifierType == GameplayModifiers::EnergyType::Bar)) {
      mainImage->set_color(Color::HSVToRGB(GameplayUtils::pingPong(Time::get_time() * 0.5F, 1.0F), 1.0F, 1.0F));
      return;
    }

    if(energy == 0.5F) {
      mainImage->set_color(config.midColor);
      return;
    }

    if(energy > 0.5F) {
      mainImage->set_color(Color::Lerp(config.midColor, config.highColor, (energy - 0.5f) * 2));
      return;
    }

    if(energy < 0.5F) {
      mainImage->set_color(Color::Lerp(config.lowColor, config.midColor, energy* 2));
    }
}

void GameplayHooks(Logger& logger) {
  INSTALL_HOOK(logger, ComboUIController_StartHook);
  INSTALL_HOOK(logger, GameEnergyUIPanel_RefreshHook);
}

ColoramaInstallHooks(GameplayHooks)