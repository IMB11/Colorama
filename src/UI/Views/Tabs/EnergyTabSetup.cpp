#include "UI/Views/ConfigViewController.hpp"

using namespace Colorama::UI;
using namespace QuestUI;
using namespace HMUI;
using namespace UnityEngine::UI;

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

void ConfigViewController::SetupEnergyTab() {
  auto _energyTab =
	    BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
	auto _energyEntries =
	    BeatSaberUI::CreateModifierContainer(_energyTab->get_transform());

	EnergyBarConfiguration energyBarConfig =
	    getColoramaConfig().energyBarConfiguration.GetValue();

    if(isRedbarInstalled()) {
      BeatSaberUI::CreateText(_energyEntries, "Redbar is installed.");
      BeatSaberUI::CreateText(_energyEntries, "This functionality is disabled.");
      BeatSaberUI::CreateText(_energyEntries, "Remove RedBar to enable.");
      this->energyTab = AdjustedScrollContainerObject(_energyTab, false);
      return;
    }

	Toggle *rainbowToggle = nullptr;
	ColorSetting *lowColor = nullptr;
	ColorSetting *midColor = nullptr;
	ColorSetting *highColor = nullptr;
	BeatSaberUI::CreateToggle(
	    _energyEntries->get_transform(), "Enabled", energyBarConfig.enabled,
	    [rainbowToggle, lowColor, midColor, highColor](bool newValue) {
	      auto cfg = getColoramaConfig().energyBarConfiguration.GetValue();
	      cfg.enabled = newValue;
	      getColoramaConfig().energyBarConfiguration.SetValue(cfg);

	      if (rainbowToggle != nullptr) {
		    rainbowToggle->set_interactable(newValue);
	      }
	      if (lowColor != nullptr) {
		    lowColor->set_interactable(newValue);
	      }
	      if (midColor != nullptr) {
		    midColor->set_interactable(newValue);
	      }
	      if (highColor != nullptr) {
		    highColor->set_interactable(newValue);
	      }
	    });

	rainbowToggle = BeatSaberUI::CreateToggle(
	    _energyEntries->get_transform(), "Rainbow When Full",
	    energyBarConfig.rainbowFull, [](bool newValue) {
	      auto cfg = getColoramaConfig().energyBarConfiguration.GetValue();
	      cfg.rainbowFull = newValue;
	      getColoramaConfig().energyBarConfiguration.SetValue(cfg);
	    });

	lowColor = BeatSaberUI::CreateColorPicker(
	    _energyEntries->get_transform(), "Low Energy Color",
	    energyBarConfig.lowColor, [](Color newValue) {
	      auto cfg = getColoramaConfig().energyBarConfiguration.GetValue();
	      cfg.lowColor = ConvertedColor::convert(newValue);
	      getColoramaConfig().energyBarConfiguration.SetValue(cfg);
	    });

	midColor = BeatSaberUI::CreateColorPicker(
	    _energyEntries->get_transform(), "Medium Energy Color",
	    energyBarConfig.midColor, [](Color newValue) {
	      auto cfg = getColoramaConfig().energyBarConfiguration.GetValue();
	      cfg.midColor = ConvertedColor::convert(newValue);
	      getColoramaConfig().energyBarConfiguration.SetValue(cfg);
	    });

	highColor = BeatSaberUI::CreateColorPicker(
	    _energyEntries->get_transform(), "High Energy Color",
	    energyBarConfig.highColor, [](Color newValue) {
	      auto cfg = getColoramaConfig().energyBarConfiguration.GetValue();
	      cfg.highColor = ConvertedColor::convert(newValue);
	      getColoramaConfig().energyBarConfiguration.SetValue(cfg);
	    });

	rainbowToggle->set_interactable(energyBarConfig.enabled);
	lowColor->set_interactable(energyBarConfig.enabled);
	midColor->set_interactable(energyBarConfig.enabled);
	highColor->set_interactable(energyBarConfig.enabled);

	BeatSaberUI::CreateSliderSetting(
	    _energyEntries->get_transform(), "Preview Value", 0.05F,
	    this->_previewViewController->fillAmount, 0.0F, 1.0F,
	    [this](float newValue) {
	      this->_previewViewController->fillAmount = newValue;
	    });

	this->energyTab = AdjustedScrollContainerObject(_energyTab, false);
}
