#include "UI/Views/ConfigViewController.hpp"

#include <utility>

#include "Coloring/ProgressBarColorizer.hpp"
#include "HMUI/SegmentedControl.hpp"
#include "HMUI/TextSegmentedControl.hpp"
#include "System/Action_2.hpp"
#include "UnityEngine/RectOffset.hpp"
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

DEFINE_TYPE(Colorama::UI, ConfigViewController)

using namespace Colorama::UI;

UnityEngine::GameObject *ConfigViewController::AdjustedScrollContainerObject(
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

void ConfigViewController::Inject(
    Colorama::Coloring::MenuColorSwapper *menuColorSwapper,
    PreviewViewController *previewViewController) {
  this->_menuColorSwapper = menuColorSwapper;
  this->_previewViewController = previewViewController;

  INFO("Injected args into ConfigViewController")
}

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

	SetupMenuTab();
    SetupEnergyTab();
    SetupMultiplierTab();
	SetupComboTab();
    SetupProgressBarTab();
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