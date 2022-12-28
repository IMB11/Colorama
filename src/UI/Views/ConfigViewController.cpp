#include "UI/Views/ConfigViewController.hpp"

DEFINE_TYPE(Colorama::UI, ConfigViewController)

using namespace Colorama::UI;

void ConfigViewController::Construct(Colorama::Coloring::MenuColorSwapper *menuColorSwapper) {
  this->_menuColorSwapper = menuColorSwapper;
}

template<::QuestUI::BeatSaberUI::HasTransform P>
inline ::QuestUI::ColorSetting* AddConfigValueColorPicker(P parent, ConfigUtils::ConfigValue<ConfigUtils::Color>& configValue) {
  auto object = ::QuestUI::BeatSaberUI::CreateColorPicker(parent, configValue.GetName(), configValue.GetValue(),
                                                          [&configValue](::UnityEngine::Color value) {
	                                                        configValue.SetValue(value);
                                                          }
  );
  if(!configValue.GetHoverHint().empty())
	::QuestUI::BeatSaberUI::AddHoverHint(object, configValue.GetHoverHint());
  return object;
}

#include "HMUI/Touchable.hpp"

void ConfigViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {
  this->_menuColorSwapper->UpdateColors();
}

void ConfigViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
  using namespace HMUI;
  using namespace UnityEngine;
  using namespace UnityEngine::UI;
  using namespace QuestUI;

  if(firstActivation) {
	get_gameObject()->AddComponent<Touchable*>();
	GameObject* scrollView = BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

	AddConfigValueToggle(scrollView->get_transform(), getColoramaConfig().Can_Menu_GamemodeColor);
	AddConfigValueColorPicker(scrollView->get_transform(), getColoramaConfig().Menu_GamemodeColor);
  }
}