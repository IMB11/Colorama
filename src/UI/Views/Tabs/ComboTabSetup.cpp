#include "UI/Views/ConfigViewController.hpp"

using namespace Colorama::UI;
using namespace QuestUI;
using namespace HMUI;
using namespace UnityEngine::UI;

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

void ConfigViewController::SetupComboTab() {
  auto _comboTab =
	    BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

	ComboConfiguration comboConfig =
	    getColoramaConfig().comboConfiguration.GetValue();

	auto modifierContainerCombo =
	    BeatSaberUI::CreateModifierContainer(_comboTab->get_transform());

	static SafePtrUnity<HorizontalLayoutGroup> nonGradientContainerHoz =
	    BeatSaberUI::CreateHorizontalLayoutGroup(_comboTab->get_transform());
	auto nonGradientContainer = BeatSaberUI::CreateVerticalLayoutGroup(
	    nonGradientContainerHoz.ptr()->get_transform());
	nonGradientContainer->set_spacing(0.25f);
	nonGradientContainer->set_padding(RectOffset::New_ctor(2, 2, 2, 2));

	static SafePtrUnity<HorizontalLayoutGroup> gradientContainerHoz =
	    BeatSaberUI::CreateHorizontalLayoutGroup(_comboTab->get_transform());
	auto gradientContainer = BeatSaberUI::CreateVerticalLayoutGroup(
	    gradientContainerHoz.ptr()->get_transform());
	gradientContainer->set_padding(RectOffset::New_ctor(2, 2, 2, 2));

	static SafePtrUnity<Toggle> gradientToggle = nullptr;
	BeatSaberUI::CreateToggle(
	    modifierContainerCombo->get_transform(), "Enabled", comboConfig.enabled,
	    [](bool newValue) {
	      auto cfg = getColoramaConfig().comboConfiguration.GetValue();
	      cfg.enabled = newValue;
	      getColoramaConfig().comboConfiguration.SetValue(cfg);

	      if (gradientToggle.ptr() != nullptr) {
		    gradientToggle.ptr()->set_interactable(newValue);
	      }

	      if (newValue) {
		    nonGradientContainerHoz.ptr()->get_gameObject()->SetActive(
		        ! cfg.useGradient);
		    gradientContainerHoz.ptr()->get_gameObject()->SetActive(
		        cfg.useGradient);
	      } else {
		    nonGradientContainerHoz.ptr()->get_gameObject()->SetActive(false);
		    gradientContainerHoz.ptr()->get_gameObject()->SetActive(false);
	      }
	    });

	gradientToggle = BeatSaberUI::CreateToggle(
	    modifierContainerCombo->get_transform(), "Use Gradient",
	    comboConfig.useGradient, [this](bool newValue) {
	      auto cfg = getColoramaConfig().comboConfiguration.GetValue();
	      cfg.useGradient = newValue;
	      getColoramaConfig().comboConfiguration.SetValue(cfg);

	      if (cfg.enabled) {
		    nonGradientContainerHoz.ptr()->get_gameObject()->SetActive(
		        ! cfg.useGradient);
		    gradientContainerHoz.ptr()->get_gameObject()->SetActive(
		        cfg.useGradient);
	      } else {
		    nonGradientContainerHoz.ptr()->get_gameObject()->SetActive(false);
		    gradientContainerHoz.ptr()->get_gameObject()->SetActive(false);
	      }

	      this->_previewViewController->UpdateComboPanel();
	    });

	// Non-Gradient

	BeatSaberUI::CreateText(nonGradientContainer->get_transform(),
	                        "<size=5><u>Simple Mode</u></size>");

	BeatSaberUI::CreateColorPicker(
	    nonGradientContainer->get_transform(), "Top Line Color",
	    comboConfig.topLineColor, [](Color newValue) {
	      auto cfg = getColoramaConfig().comboConfiguration.GetValue();
	      cfg.topLineColor = ConvertedColor::convert(newValue);
	      getColoramaConfig().comboConfiguration.SetValue(cfg);
	    });

	BeatSaberUI::CreateColorPicker(
	    nonGradientContainer->get_transform(), "Bottom Line Color",
	    comboConfig.bottomLineColor, [](Color newValue) {
	      auto cfg = getColoramaConfig().comboConfiguration.GetValue();
	      cfg.bottomLineColor = ConvertedColor::convert(newValue);
	      getColoramaConfig().comboConfiguration.SetValue(cfg);
	    });

	// Gradient

	BeatSaberUI::CreateText(gradientContainer->get_transform(),
	                        "<size=5><u>Gradient Mode</u></size>");
	// clang-format off
#define GRADIENT_COL_PICK(name, val)                      \
  BeatSaberUI::CreateColorPicker(  \
  gradientContainer->get_transform(),                                   \
  name, comboConfig.val,                   \
  [](Color newValue) {         \
	auto cfg = getColoramaConfig().comboConfiguration.GetValue(); \
	cfg.val = ConvertedColor::convert(newValue); \
	getColoramaConfig().comboConfiguration.SetValue(cfg); \
  });
	// clang-format on

	GRADIENT_COL_PICK("Top Left", topLeft);
	GRADIENT_COL_PICK("Top Right", topRight);
	static SafePtrUnity<ColorSetting> btl =
	    GRADIENT_COL_PICK("Bottom Left", bottomLeft);
	static SafePtrUnity<ColorSetting> btr =
	    GRADIENT_COL_PICK("Bottom Right", bottomRight);

	BeatSaberUI::CreateToggle(
	    gradientContainer->get_transform(), "Mirror Top To Bottom",
	    comboConfig.mirrorToBottom,
	    [](bool newValue) {
	      auto cfg = getColoramaConfig().comboConfiguration.GetValue();
	      cfg.mirrorToBottom = newValue;
	      getColoramaConfig().comboConfiguration.SetValue(cfg);
	      btl.ptr()->set_interactable(! newValue);
	      btr.ptr()->set_interactable(! newValue);
	    })
	    ->get_transform()
	    ->SetSiblingIndex(1);

	// ==============================

	nonGradientContainerHoz->get_gameObject()->SetActive(
	    ! comboConfig.useGradient);
	gradientContainerHoz->get_gameObject()->SetActive(comboConfig.useGradient);

	this->comboTab = AdjustedScrollContainerObject(_comboTab, false);
}
