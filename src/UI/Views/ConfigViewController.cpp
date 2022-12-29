#include "UI/Views/ConfigViewController.hpp"

#include <utility>

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

void ConfigViewController::Construct(
    Colorama::Coloring::MenuColorSwapper *menuColorSwapper, PreviewViewController* previewViewController) {
  this->_menuColorSwapper = menuColorSwapper;
  this->_previewViewController = previewViewController;
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

	MenuConfiguration configuration = getColoramaConfig().menuConfiguration.GetValue();

#define CPE(title, subValue) \
	CreateColorPickerEnable( \
		_menuTab->get_transform(), title, \
		configuration.subValue.enabled, \
	    configuration.subValue, \
		[this](bool newValue) { \
		  auto cfg = getColoramaConfig().menuConfiguration.GetValue(); \
	      cfg.subValue.enabled = newValue;\
	      getColoramaConfig().menuConfiguration.SetValue(cfg, false); \
		  this->_menuColorSwapper->UpdateColors(); \
		}, \
		[this](Color newValue) {   \
	      auto cfg = getColoramaConfig().menuConfiguration.GetValue(); \
	      auto newPair = ColorPair::convert(newValue, cfg.subValue.enabled); \
	      cfg.subValue = newPair; \
	      getColoramaConfig().menuConfiguration.SetValue(cfg, false); \
	      this->_menuColorSwapper->UpdateColors(); \
		}, \
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

	auto vertGroup_menuTab = BeatSaberUI::CreateVerticalLayoutGroup(_menuTab->get_transform());

#define CMT(title, configValue) \
	BeatSaberUI::CreateToggle(vertGroup_menuTab->get_transform(), title, configuration.configValue, [this](bool newValue) { \
      auto cfg = getColoramaConfig().menuConfiguration.GetValue(); \
	  cfg.configValue = newValue; \
	  getColoramaConfig().menuConfiguration.SetValue(cfg, false); \
	  this->_menuColorSwapper->UpdateColors(); \
	});

	CMT("Enable Fog Ring", enableFogRing)
    CMT("Enable Menu Floor", enableFloor)
	CMT("Enable Note Decor", enableNoteDecor)
	CMT("Enable Logo Glow Lines", enableLogoGlowLines)

	this->menuTab =
	    AdjustedScrollContainerObject(_menuTab->get_gameObject(), true);

#pragma endregion

	DEFINE_TAB(energyTab, false)
	DEFINE_TAB(multiplierRingTab, false)
	DEFINE_TAB(progressBarTab, false)
	DEFINE_TAB(comboTab, false)
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