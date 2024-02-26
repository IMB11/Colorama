#include "UI/Views/ConfigViewController.hpp"

using namespace Colorama::UI;
using namespace QuestUI;
using namespace HMUI;
using namespace UnityEngine::UI;

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

void ConfigViewController::SetupMultiplierTab() {
  auto _multiplierTab =
	    BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

	auto _multiplierEntries =
	    BeatSaberUI::CreateModifierContainer(_multiplierTab->get_transform());

	MultiplierConfig multiplierConfig =
	    getColoramaConfig().multiplierConfiguration.GetValue();

	static SafePtrUnity<HorizontalLayoutGroup> _multiplierHoz =
	    BeatSaberUI::CreateHorizontalLayoutGroup(
	        _multiplierTab->get_transform());
	auto _multiplierContainer = BeatSaberUI::CreateVerticalLayoutGroup(
	    _multiplierHoz.ptr()->get_transform());
	_multiplierContainer->set_spacing(0.25f);
	_multiplierContainer->set_padding(RectOffset::New_ctor(2, 2, 2, 2));

	static SafePtrUnity<Toggle> rainbow8Toggle = nullptr;
	static SafePtrUnity<ColorSetting> _8Color = nullptr;
	BeatSaberUI::CreateToggle(
	    _multiplierEntries->get_transform(), "Enabled",
	    multiplierConfig.enabled, [_multiplierContainer](bool newValue) {
	      auto cfg = getColoramaConfig().multiplierConfiguration.GetValue();
	      cfg.enabled = newValue;
	      getColoramaConfig().multiplierConfiguration.SetValue(cfg);

	      if (rainbow8Toggle.ptr() != nullptr) {
		    rainbow8Toggle.ptr()->set_interactable(newValue);
	      }

	      _multiplierContainer->get_gameObject()->SetActive(newValue);
	    });

	rainbow8Toggle = BeatSaberUI::CreateToggle(
	    _multiplierEntries->get_transform(), "Enable Rainbow x8",
	    multiplierConfig.enableRainbow, [](bool newValue) {
	      auto cfg = getColoramaConfig().multiplierConfiguration.GetValue();
	      cfg.enableRainbow = newValue;
	      getColoramaConfig().multiplierConfiguration.SetValue(cfg);

	      if (_8Color.ptr() != nullptr) {
		    _8Color.ptr()->set_interactable(! newValue);
	      }
	    });

	BeatSaberUI::CreateColorPicker(
	    _multiplierContainer->get_transform(), "x1 Multiplier Color",
	    multiplierConfig.oneColor, [](Color newValue) {
	      auto cfg = getColoramaConfig().multiplierConfiguration.GetValue();
	      cfg.oneColor = ConvertedColor::convert(newValue);
	      getColoramaConfig().multiplierConfiguration.SetValue(cfg);
	    });

	BeatSaberUI::CreateColorPicker(
	    _multiplierContainer->get_transform(), "x2 Multiplier Color",
	    multiplierConfig.twoColor, [](Color newValue) {
	      auto cfg = getColoramaConfig().multiplierConfiguration.GetValue();
	      cfg.twoColor = ConvertedColor::convert(newValue);
	      getColoramaConfig().multiplierConfiguration.SetValue(cfg);
	    });

	BeatSaberUI::CreateColorPicker(
	    _multiplierContainer->get_transform(), "x4 Multiplier Color",
	    multiplierConfig.fourColor, [](Color newValue) {
	      auto cfg = getColoramaConfig().multiplierConfiguration.GetValue();
	      cfg.fourColor = ConvertedColor::convert(newValue);
	      getColoramaConfig().multiplierConfiguration.SetValue(cfg);
	    });

	_8Color = BeatSaberUI::CreateColorPicker(
	    _multiplierContainer->get_transform(), "x8 Multiplier Color",
	    multiplierConfig.eightColor, [](Color newValue) {
	      auto cfg = getColoramaConfig().multiplierConfiguration.GetValue();
	      cfg.eightColor = ConvertedColor::convert(newValue);
	      getColoramaConfig().multiplierConfiguration.SetValue(cfg);
	    });

	this->multiplierRingTab =
	    AdjustedScrollContainerObject(_multiplierTab, false);
}
