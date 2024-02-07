#include "UI/Views/ConfigViewController.hpp"

#include <utility>

#include "Coloring/ProgressBarColorizer.hpp"
#include "HMUI/SegmentedControl.hpp"
#include "HMUI/TextSegmentedControl.hpp"
#include "System/Action_2.hpp"
#include "custom-types/shared/delegate.hpp"
#include "questui/shared/CustomTypes/Components/ExternalComponents.hpp"

#define MakeADelegate(DelegateType, varName) \
  (custom_types::MakeDelegate<DelegateType>(varName))

QuestUI::CustomTextSegmentedControlData *CreateTextSegmentedControlFIX(
    UnityEngine::Transform *parent, UnityEngine::Vector2 anchoredPosition,
    UnityEngine::Vector2 sizeDelta, ArrayW<StringW> values,
    const std::function<void(int)> &onCellWithIdxClicked) {
  static SafePtrUnity<HMUI::TextSegmentedControl> segmentedControlTemplate;
  if (! segmentedControlTemplate)
	segmentedControlTemplate =
	    UnityEngine::Resources::FindObjectsOfTypeAll<
	        HMUI::TextSegmentedControl *>()
	        .FirstOrDefault(
	            [](auto x) { return x->get_name() == "TextSegmentedControl"; });

  auto segmentedControlObj = UnityEngine::Object::Instantiate(
      segmentedControlTemplate->get_gameObject(), parent, false);
  segmentedControlObj->SetActive(false);
  static ConstString QuestUITextSegmentedControl("QuestUITextSegmentedControl");
  segmentedControlObj->set_name(QuestUITextSegmentedControl);
  auto rectTransform = reinterpret_cast<UnityEngine::RectTransform *>(
      segmentedControlObj->get_transform());
  rectTransform->set_sizeDelta(sizeDelta);
  rectTransform->set_anchoredPosition(anchoredPosition);

  UnityEngine::Object::DestroyImmediate(
      segmentedControlObj->GetComponent<HMUI::TextSegmentedControl *>());
  auto control = segmentedControlObj->AddComponent<HMUI::SegmentedControl *>();
  auto result = segmentedControlObj
                    ->AddComponent<QuestUI::CustomTextSegmentedControlData *>();

  result->firstCellPrefab = segmentedControlTemplate->firstCellPrefab;
  result->lastCellPrefab = segmentedControlTemplate->lastCellPrefab;
  result->middleCellPrefab = segmentedControlTemplate->middleCellPrefab;
  result->singleCellPrefab = segmentedControlTemplate->singleCellPrefab;

  result->segmentedControl = control;
  control->dataSource =
      reinterpret_cast<HMUI::SegmentedControl::IDataSource *>(result);

  if (onCellWithIdxClicked) {
	using DelegateType = System::Action_2<HMUI::SegmentedControl *, int> *;
	std::function<void(HMUI::SegmentedControl *, int)> fun =
	    [onCellWithIdxClicked](HMUI::SegmentedControl *cell, int idx) {
	      onCellWithIdxClicked(idx);
	    };
	auto delegate = MakeADelegate(DelegateType, fun);
	control->add_didSelectCellEvent(delegate);
  }

  int childCount = result->get_transform()->get_childCount();
  for (int i = 0; i < childCount; i++) {
	UnityEngine::Object::DestroyImmediate(
	    result->get_transform()->GetChild(0)->get_gameObject());
  }

  result->set_texts(values);

  segmentedControlObj->SetActive(true);
  return result;
}

UnityEngine::GameObject *AdjustedScrollContainerObject(
    UnityEngine::GameObject *container, bool active) {
  using namespace GlobalNamespace;
  using namespace QuestUI;
  using namespace UnityEngine;

  auto extComponents = container->GetComponent<ExternalComponents *>();
  auto scrollTransform = extComponents->Get<RectTransform *>();
  scrollTransform->set_anchoredPosition(Vector2(0.0f, -5.0f));
  scrollTransform->get_gameObject()->SetActive(active);
  return scrollTransform->get_gameObject();
}

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
UnityEngine::GameObject *CreateColorPickerEnable(
    UnityEngine::Transform *parent, std::string title, bool initialValue,
    Color initialColor, const std::function<void(bool)> &onToggle,
    std::function<void(Color)> onSaveColor,
    const SafePtr<Colorama::Coloring::MenuColorSwapper> &menuColorSwapper) {
  using namespace HMUI;
  using namespace UnityEngine;
  using namespace UnityEngine::UI;
  using namespace QuestUI;

  auto *horizontalLayoutGroup =
      BeatSaberUI::CreateHorizontalLayoutGroup(parent);
  auto *groupBackgroundable =
      horizontalLayoutGroup->GetComponent<Backgroundable *>();

  auto vertGroup = BeatSaberUI::CreateVerticalLayoutGroup(
      horizontalLayoutGroup->get_transform());
  vertGroup->set_spacing(0.25f);
  vertGroup->set_padding(RectOffset::New_ctor(2, 2, 2, 2));

  ColorSetting *picker = BeatSaberUI::CreateColorPicker(
      vertGroup->get_transform(), "Color", initialColor, std::move(onSaveColor),
      nullptr, [menuColorSwapper](Color testColor) {
	    menuColorSwapper->PreviewColor(testColor);
      });

  BeatSaberUI::CreateToggle(
      vertGroup->get_transform(),
      "<size=5><u>" + std::move(title) + "</u></size>", initialValue,
      [onToggle, picker](bool newValue) {
	    onToggle(newValue);
	    picker->set_interactable(newValue);
	    picker->GetComponentInChildren<TMPro::TextMeshProUGUI *>()->set_color(
	        newValue ? Color::get_white() : Color::get_gray());
      });

  picker->get_transform()->SetAsLastSibling();
  picker->set_interactable(initialValue);
  picker->GetComponentInChildren<TMPro::TextMeshProUGUI *>()->set_color(
      initialValue ? Color::get_white() : Color::get_gray());

  return horizontalLayoutGroup->get_gameObject();
}

DEFINE_TYPE(Colorama::UI, ConfigViewController)

using namespace Colorama::UI;

void ConfigViewController::Inject(
    Colorama::Coloring::MenuColorSwapper *menuColorSwapper,
    PreviewViewController *previewViewController) {
  this->_menuColorSwapper = menuColorSwapper;
  this->_previewViewController = previewViewController;

  INFO("Injected args into ConfigViewController")
}

template <::QuestUI::BeatSaberUI::HasTransform P>
inline ::QuestUI::ColorSetting *AddConfigValueColorPicker(
    P parent, ConfigUtils::ConfigValue<ConfigUtils::Color> &configValue) {
  auto object = ::QuestUI::BeatSaberUI::CreateColorPicker(
      parent, configValue.GetName(), configValue.GetValue(),
      [&configValue](::UnityEngine::Color value) {
	    configValue.SetValue(value);
      });
  if (! configValue.GetHoverHint().empty())
	::QuestUI::BeatSaberUI::AddHoverHint(object, configValue.GetHoverHint());
  return object;
}

#include "HMUI/Touchable.hpp"
#include "UnityEngine/UI/Selectable.hpp"

void ConfigViewController::DidDeactivate(bool removedFromHierarchy,
                                         bool screenSystemDisabling) {
  this->_menuColorSwapper->UpdateColors();
}

#define DEFINE_TAB(store, active, ...)                                 \
  auto _##store =                                                      \
      BeatSaberUI::CreateScrollableSettingsContainer(get_transform()); \
  __VA_ARGS__                                                          \
  this->store = AdjustedScrollContainerObject(_##store, active);

void ConfigViewController::DidActivate(bool firstActivation,
                                       bool addedToHierarchy,
                                       bool screenSystemEnabling) {
  using namespace HMUI;
  using namespace UnityEngine;
  using namespace UnityEngine::UI;
  using namespace QuestUI;

  static ArrayW<StringW> options(5);
  options[0] = "Menu";
  options[1] = "Energy Bar";
  options[2] = "Multiring";
  options[3] = "Progress Bar";
  options[4] = "Combo Indicator";

  if (firstActivation) {
	auto root = BeatSaberUI::CreateVerticalLayoutGroup(get_transform());
	root->set_childControlHeight(false);

	CreateTextSegmentedControlFIX(root->get_transform(), {0, 0}, Vector2(75, 7),
	                              options, [this](int idx) { SwitchTab(idx); });

#pragma region Menu Colors Tab

	auto _menuTab =
	    BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
	//	_menuTab->GetComponent<VerticalLayoutGroup*>()->set_childForceExpandWidth(true);
	//	_menuTab->get_gameObject()->GetComponent<ContentSizeFitter*>()->set_horizontalFit(ContentSizeFitter::FitMode::_get_PreferredSize());

	auto headerA = BeatSaberUI::CreateText(_menuTab->get_transform(),
	                                       "Menu Lighting", false);
	headerA->set_alignment(TMPro::TextAlignmentOptions::_get_Center());
	headerA->set_color(Color::get_gray());

	MenuConfiguration configuration =
	    getColoramaConfig().menuConfiguration.GetValue();

#define CPE(title, subValue)                                               \
  CreateColorPickerEnable(                                                 \
      _menuTab->get_transform(), title, configuration.subValue.enabled,    \
      configuration.subValue,                                              \
      [this](bool newValue) {                                              \
	    auto cfg = getColoramaConfig().menuConfiguration.GetValue();       \
	    cfg.subValue.enabled = newValue;                                   \
	    getColoramaConfig().menuConfiguration.SetValue(cfg, false);        \
	    this->_menuColorSwapper->UpdateColors();                           \
      },                                                                   \
      [this](Color newValue) {                                             \
	    auto cfg = getColoramaConfig().menuConfiguration.GetValue();       \
	    auto newPair = ColorPair::convert(newValue, cfg.subValue.enabled); \
	    cfg.subValue = newPair;                                            \
	    getColoramaConfig().menuConfiguration.SetValue(cfg, false);        \
	    this->_menuColorSwapper->UpdateColors();                           \
      },                                                                   \
      this->_menuColorSwapper);

	CPE("Gamemode Selection Menu", gamemodeLighting);
	CPE("Solo/Party Menu", freeplayLighting);
	CPE("Campaign Menu", campaignLighting);
	CPE("Multiplayer Lobby (Idle)", multiplayerIdleColor);
	CPE("Multiplayer Lobby (Countdown)", multiplayerCountdownColor);
	CPE("Results Menu (Pass)", resultsLighting);
	CPE("Results Menu (Fail)", resultsFailLighting);

	auto headerB = BeatSaberUI::CreateText(_menuTab->get_transform(),
	                                       "Menu Environment", false);
	headerB->set_alignment(TMPro::TextAlignmentOptions::_get_Center());
	headerB->set_color(Color::get_gray());

	auto vertGroup_menuTab =
	    BeatSaberUI::CreateModifierContainer(_menuTab->get_transform());

#define CMT(title, configValue)                                             \
  BeatSaberUI::CreateToggle(                                                \
      vertGroup_menuTab->get_transform(), title, configuration.configValue, \
      [this](bool newValue) {                                               \
	    auto cfg = getColoramaConfig().menuConfiguration.GetValue();        \
	    cfg.configValue = newValue;                                         \
	    getColoramaConfig().menuConfiguration.SetValue(cfg, false);         \
	    this->_menuColorSwapper->UpdateColors();                            \
      });

	CMT("Enable Fog Ring", enableFogRing)
	CMT("Enable Menu Floor", enableFloor)
	CMT("Enable Note Decor", enableNoteDecor)
	CMT("Enable Logo Glow Lines", enableLogoGlowLines)

	this->menuTab =
	    AdjustedScrollContainerObject(_menuTab->get_gameObject(), true);

#pragma endregion

#pragma region Energy Bar Tab
	auto _energyTab =
	    BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
	auto _energyEntries =
	    BeatSaberUI::CreateModifierContainer(_energyTab->get_transform());

	EnergyBarConfiguration energyBarConfig =
	    getColoramaConfig().energyBarConfiguration.GetValue();

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

#pragma endregion

#pragma region Multiplier Ring Tab
	auto _multiplierTab =
	    BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
	auto _multiplierEntries =
	    BeatSaberUI::CreateModifierContainer(_multiplierTab->get_transform());

#ifdef ENABLE_KOFI_FEATURES
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
#else

	auto text1 = BeatSaberUI::CreateText(_multiplierEntries->get_transform(),
	                                     "Kofi Features Disabled");
	text1->set_color(Color::get_red());

	BeatSaberUI::CreateText(
	    _multiplierEntries->get_transform(),
	    "The multiplier ring colorizer is currently in beta, and only "
	    "available to Ko-Fi supporters for testing.");
	BeatSaberUI::CreateText(
	    _multiplierEntries->get_transform(),
	    "If you would like to support the development of this feature, please "
	    "consider becoming a member at the link below.");
	BeatSaberUI::CreateText(_multiplierEntries->get_transform(),
	                        "https://ko-fi.com/mineblock11");

#endif

	this->multiplierRingTab =
	    AdjustedScrollContainerObject(_multiplierTab, false);

#pragma endregion

#pragma region Combo Tab
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
#pragma endregion

#pragma region Progress Bar Tab

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
#pragma endregion
  }
}

void ConfigViewController::SwitchTab(int idx) {
  this->_previewViewController->UpdatePanelVisibility(idx);

  menuTab->SetActive(idx == 0);
  energyTab->SetActive(idx == 1);
  multiplierRingTab->SetActive(idx == 2);
  progressBarTab->SetActive(idx == 3);
  comboTab->SetActive(idx == 4);
}