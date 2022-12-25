#include "Coloring/Services/DefaultMenuService.hpp"

#include "GlobalNamespace/SimpleColorSO.hpp"
#include "GlobalNamespace/EaseType.hpp"

#include "Tweening/ColorTween.hpp"
#include "System/Action_1.hpp"
#include "System/Action.hpp"

#include "custom-types/shared/delegate.hpp"

#include <optional>

DEFINE_TYPE(Colorama::Coloring::Services, DefaultMenuService)

void Colorama::Coloring::Services::DefaultMenuService::ctor(GlobalNamespace::MenuLightsManager *lightsManager, Tweening::Tween *tween) {
  this->_lightsManager = lightsManager;
  this->_tween = tween;
}

void Colorama::Coloring::Services::DefaultMenuService::set_v_color(UnityEngine::Color color) {
  this->_color = color;
  SetColor(color);
}

UnityEngine::Color Colorama::Coloring::Services::DefaultMenuService::get_v_color() {
  return this->_color;
}

StringW Colorama::Coloring::Services::DefaultMenuService::get_v_name() {
  return "Normal Menu Color";
}

std::reference_wrapper<ConfigUtils::ConfigValue<ConfigUtils::Color>> Colorama::Coloring::Services::DefaultMenuService::get_v_relatedValue() {
  return std::ref(getColoramaConfig().Menu_FreeplayColor);
}

void Colorama::Coloring::Services::DefaultMenuService::SetColor(UnityEngine::Color color) {
  this->_lightsManager->SetColor(MENU_LIGHT_ID, color);

  std::optional<UnityEngine::Color> coloropt = std::nullopt;

  auto defaultPreset = this->_lightsManager->defaultPreset;
  auto colorPairs = defaultPreset->lightIdColorPairs;
  for (auto pair : colorPairs) {
    if(pair->lightId != 1) {
      continue;
    }

    if(is_inst<GlobalNamespace::SimpleColorSO*>(pair->baseColor)) {
      auto simpleBaseColor = il2cpp_utils::cast<GlobalNamespace::SimpleColorSO>(pair->baseColor);
      coloropt = std::optional(pair->baseColor->get_color());
      simpleBaseColor->SetColor(color);
      return;
    }
  }

  if(!coloropt.has_value()) return;

  if(_tween != nullptr) {
    _tween->Kill();
  }

  std::function delegateAction_1_UE_Color = [](UnityEngine::Color _delegateColor) {

  };

  std::function delegateAction_tweenCompleted = []() {

  };

  _tween = Tweening::ColorTween::New_ctor(
      coloropt.value(),
      color,
      custom_types::MakeDelegate<System::Action_1<UnityEngine::Color>*>(delegateAction_1_UE_Color),
      0.5f,
      GlobalNamespace::EaseType::Linear,
      0.0f);

  _tween->onCompleted = custom_types::MakeDelegate<System::Action*>(delegateAction_tweenCompleted);
  _tweeningManager->AddTween(_tween, _lightsManager);
}