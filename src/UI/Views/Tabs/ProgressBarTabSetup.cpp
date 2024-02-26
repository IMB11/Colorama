#include "UI/Views/ConfigViewController.hpp"

using namespace Colorama::UI;
using namespace QuestUI;
using namespace HMUI;
using namespace UnityEngine::UI;

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

void ConfigViewController::SetupProgressBarTab() {
  auto _progressBarTab =
	    BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

	ProgressBarConfiguration progressConfig =
	    getColoramaConfig().progressBarConfiguration.GetValue();

	VerticalLayoutGroup *_progressEntries =
	    BeatSaberUI::CreateModifierContainer(_progressBarTab->get_transform());

	static SafePtrUnity<HorizontalLayoutGroup> progressSimpleHoz =
	    BeatSaberUI::CreateHorizontalLayoutGroup(
	        _progressBarTab->get_transform());
	auto progressSimple = BeatSaberUI::CreateVerticalLayoutGroup(
	    progressSimpleHoz.ptr()->get_transform());
	progressSimple->set_padding(RectOffset::New_ctor(2, 2, 2, 2));

	BeatSaberUI::CreateText(progressSimple->get_transform(),
	                        "<size=5><u>Simple Mode</u></size>");

	static SafePtrUnity<HorizontalLayoutGroup> progressGradientHoz =
	    BeatSaberUI::CreateHorizontalLayoutGroup(
	        _progressBarTab->get_transform());
	auto progressGradient = BeatSaberUI::CreateVerticalLayoutGroup(
	    progressGradientHoz.ptr()->get_transform());
	progressGradient->set_padding(RectOffset::New_ctor(2, 2, 2, 2));

	BeatSaberUI::CreateText(progressGradient->get_transform(),
	                        "<size=5><u>Gradient Mode</u></size>");

	static SafePtrUnity<Toggle> gradientToggleProgress = nullptr;
	static SafePtrUnity<ColorSetting> progressHandle = nullptr;
	static SafePtrUnity<ColorSetting> progressBg = nullptr;
	static SafePtrUnity<SliderSetting> previewFillSlider = nullptr;
	BeatSaberUI::CreateToggle(
	    _progressEntries->get_transform(), "Enabled", progressConfig.enabled,
	    [progressGradient, progressSimple](bool newValue) {
	      auto cfg = getColoramaConfig().progressBarConfiguration.GetValue();
	      cfg.enabled = newValue;
	      getColoramaConfig().progressBarConfiguration.SetValue(cfg);

	      if (gradientToggleProgress.ptr() != nullptr) {
		    gradientToggleProgress.ptr()->set_interactable(newValue);
	      }

	      if (previewFillSlider.ptr() != nullptr) {
		    previewFillSlider.ptr()->slider->set_interactable(newValue);
	      }

	      if (progressHandle.ptr() != nullptr) {
		    progressHandle.ptr()->set_interactable(newValue);
	      }

	      if (progressBg.ptr() != nullptr) {
		    progressBg.ptr()->set_interactable(newValue);
	      }

	      progressGradient->get_gameObject()->SetActive(newValue &&
	                                                    cfg.enableGradient);
	      progressSimple->get_gameObject()->SetActive(newValue &&
	                                                  ! cfg.enableGradient);

	      progressSimple->CalculateLayoutInputVertical();
	      progressGradient->CalculateLayoutInputVertical();
	    });

	previewFillSlider = BeatSaberUI::CreateSliderSetting(
	    _progressEntries->get_transform(), "Preview Fill", 0.01F,
	    this->_previewViewController->progressFillAmount, 0.0F, 1.0F,
	    [this](float newValue) {
	      this->_previewViewController->progressFillAmount = newValue;
	    });

	gradientToggleProgress = BeatSaberUI::CreateToggle(
	    _progressEntries->get_transform(), "Use Gradient",
	    progressConfig.enableGradient,
	    [progressGradient, progressSimple](bool newValue) {
	      auto cfg = getColoramaConfig().progressBarConfiguration.GetValue();
	      cfg.enableGradient = newValue;
	      getColoramaConfig().progressBarConfiguration.SetValue(cfg);
	      progressGradient->get_gameObject()->SetActive(newValue &&
	                                                    cfg.enabled);
	      progressSimple->get_gameObject()->SetActive(! newValue &&
	                                                  cfg.enabled);
	    });

	progressBg = BeatSaberUI::CreateColorPicker(
	    _progressEntries->get_transform(), "Background Color",
	    progressConfig.bgColor, [](Color newValue) {
	      auto cfg = getColoramaConfig().progressBarConfiguration.GetValue();
	      cfg.bgColor = ConvertedColor::convert(newValue);
	      getColoramaConfig().progressBarConfiguration.SetValue(cfg);
	    });

	progressHandle = BeatSaberUI::CreateColorPicker(
	    _progressEntries->get_transform(), "Handle Color",
	    progressConfig.handleColor, [](Color newValue) {
	      auto cfg = getColoramaConfig().progressBarConfiguration.GetValue();
	      cfg.handleColor = ConvertedColor::convert(newValue);
	      getColoramaConfig().progressBarConfiguration.SetValue(cfg);
	    });

	BeatSaberUI::CreateColorPicker(
	    progressGradient->get_transform(), "Start Color",
	    progressConfig.startColor, [](Color newValue) {
	      auto cfg = getColoramaConfig().progressBarConfiguration.GetValue();
	      cfg.startColor = ConvertedColor::convert(newValue);
	      getColoramaConfig().progressBarConfiguration.SetValue(cfg);
	    });

	BeatSaberUI::CreateColorPicker(
	    progressGradient->get_transform(), "End Color", progressConfig.endColor,
	    [](Color newValue) {
	      auto cfg = getColoramaConfig().progressBarConfiguration.GetValue();
	      cfg.endColor = ConvertedColor::convert(newValue);
	      getColoramaConfig().progressBarConfiguration.SetValue(cfg);
	    });

	BeatSaberUI::CreateColorPicker(
	    progressSimple->get_transform(), "Fill Color", progressConfig.fillColor,
	    [](Color newValue) {
	      auto cfg = getColoramaConfig().progressBarConfiguration.GetValue();
	      cfg.fillColor = ConvertedColor::convert(newValue);
	      getColoramaConfig().progressBarConfiguration.SetValue(cfg);
	    });

	progressSimple->get_gameObject()->SetActive(
	    ! progressConfig.enableGradient && progressConfig.enabled);
	progressGradient->get_gameObject()->SetActive(
	    progressConfig.enableGradient && progressConfig.enabled);
	gradientToggleProgress.ptr()->set_interactable(progressConfig.enabled);
	previewFillSlider.ptr()->slider->set_interactable(progressConfig.enabled);
	progressHandle.ptr()->set_interactable(progressConfig.enabled);
	progressBg.ptr()->set_interactable(progressConfig.enabled);

	this->progressBarTab =
	    AdjustedScrollContainerObject(_progressBarTab, false);
}