#include "Coloring/EnergyBarColorizer.hpp"

#include <UnityEngine/WaitUntil.hpp>

DEFINE_TYPE(Colorama::Coloring, EnergyBarColorizer);

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace Colorama::Coloring;

namespace EnergyBarUtils {
float repeat(float t, float length = 1.0F) {
  return std::clamp(t - std::floor(t / length) * length, 0.0f, length);
}

float pingPong(float t, float length = 1.0F) {
  t = repeat(t, length * 2.0F);
  return length - std::abs(t - length);
}
}  // namespace EnergyBarUtils

#include "GlobalNamespace/GameEnergyUIPanel.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"
#include "GlobalNamespace/IGameEnergyCounter.hpp"
#include "System/Action_1.hpp"
#include "System/Func_1.hpp"
#include "UnityEngine/Time.hpp"

void EnergyBarColorizer::Construct(GameEnergyUIPanel* energyPanel) {
  this->energyPanel = energyPanel;
}

void EnergyBarColorizer::Update() {
  if (this->energyPanel == nullptr) return;

  EnergyBarConfiguration config =
      getColoramaConfig().energyBarConfiguration.GetValue();
  IGameEnergyCounter* counter = this->energyPanel->gameEnergyCounter;
  float energy = counter->get_energy();

  if (! config.enabled) return;

  if (config.rainbowFull &&
      (this->energyPanel->gameEnergyCounter->get_instaFail() ||
       (energy == 1.0F &&
        counter->get_energyType() == GameplayModifiers::EnergyType::Bar))) {
	mainImage->set_color(Color::HSVToRGB(
	    EnergyBarUtils::pingPong(Time::get_time() * 0.5F, 1.0F), 1.0F, 1.0F));
  }
}

custom_types::Helpers::Coroutine EnergyBarColorizer::PrepareColors() {
  std::function predicate_func = [this]() {
	return this->energyPanel != nullptr;
  };
  System::Func_1<bool>* predicate =
      custom_types::MakeDelegate<System::Func_1<bool>*>(predicate_func);
  co_yield reinterpret_cast<System::Collections::IEnumerator*>(
      WaitUntil::New_ctor(predicate));

  EnergyBarConfiguration config =
      getColoramaConfig().energyBarConfiguration.GetValue();
  IGameEnergyCounter* counter = this->energyPanel->gameEnergyCounter;

  if (counter->get_energyType() == GameplayModifiers::EnergyType::Battery) {
	ListW<UnityEngine::UI::Image*> segments =
	    this->energyPanel->batteryLifeSegments;
	segments[0]->set_color(config.lowColor);
	segments[1]->set_color(
	    Color::Lerp(config.lowColor, config.midColor, 0.34F));
	segments[2]->set_color(
	    Color::Lerp(config.midColor, config.highColor, 0.66F));
	segments[3]->set_color(config.highColor);
	co_return;
  }

  mainImage = this->energyPanel->energyBar;
  if (counter->get_energyType() == GameplayModifiers::EnergyType::Battery) {
	if (counter->get_instaFail()) {
	  mainImage->set_color(config.highColor);
	} else {
	  mainImage->set_color(config.midColor);
	}
  }

  std::function<void(float)> rawFunc = std::bind(
      &EnergyBarColorizer::HandleEnergyChange, this, std::placeholders::_1);
  counter->add_gameEnergyDidChangeEvent(
      custom_types::MakeDelegate<System::Action_1<float>*>(rawFunc));

  this->HandleEnergyChange(counter->get_energy());

  co_return;
}

void EnergyBarColorizer::HandleEnergyChange(float energy) {
  EnergyBarConfiguration config =
      getColoramaConfig().energyBarConfiguration.GetValue();

  if (! config.enabled) return;

  if (energy == 0.5F) {
	mainImage->set_color(config.midColor);
	return;
  }

  if (energy > 0.5F) {
	mainImage->set_color(
	    Color::Lerp(config.midColor, config.highColor, (energy - 0.5f) * 2));
	return;
  }

  if (energy < 0.5F) {
	mainImage->set_color(
	    Color::Lerp(config.lowColor, config.midColor, energy * 2));
  }
}

void EnergyBarColorizer::Start() {
  EnergyBarConfiguration config =
      getColoramaConfig().energyBarConfiguration.GetValue();
  if (! config.enabled || isRedbarInstalled()) {
    Destroy(this);
    return;
  }

  StartCoroutine(custom_types::Helpers::CoroutineHelper::New(PrepareColors()));
}

MAKE_HOOK_MATCH(GameEnergyUIPanel_InitHook, &GameEnergyUIPanel::Init, void,
                GameEnergyUIPanel* self) {
  GameEnergyUIPanel_InitHook(self);
  self->get_gameObject()->AddComponent<EnergyBarColorizer*>()->Construct(self);
}

void EnergyBarColorizerHooks(Logger& logger) {
  if(isRedbarInstalled()) return;

  INSTALL_HOOK(logger, GameEnergyUIPanel_InitHook);
}

ColoramaInstallHooks(EnergyBarColorizerHooks)