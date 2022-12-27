#include "UI/ConfigViewController.hpp"

DEFINE_TYPE(Colorama::UI, ConfigViewController)

using namespace Colorama::UI;

void ConfigViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
  using namespace UnityEngine;
  using namespace GlobalNamespace;
  using namespace QuestUI;

  static auto* parent = il2cpp_utils::cast<Colorama::UI::ColoramaFlowCoordinator>(_parentFlowCoordinator);

  if(firstActivation) {
    auto text = BeatSaberUI::CreateText(get_transform(), string_format("Hello Zenject! There are %d ColorizerServices!", parent->_colorizerServices->size));
    text->set_color(UnityEngine::Color::get_red());
  }
}