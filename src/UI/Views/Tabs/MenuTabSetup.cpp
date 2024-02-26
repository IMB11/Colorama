#include "UI/Views/ConfigViewController.hpp"

using namespace Colorama::UI;
using namespace QuestUI;

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

#define CMT(title, configValue)                                             \
  BeatSaberUI::CreateToggle(                                                \
      vertGroup_menuTab->get_transform(), title, configuration.configValue, \
      [this](bool newValue) {                                               \
	    auto cfg = getColoramaConfig().menuConfiguration.GetValue();        \
	    cfg.configValue = newValue;                                         \
	    getColoramaConfig().menuConfiguration.SetValue(cfg, false);         \
	    this->_menuColorSwapper->UpdateColors();                            \
      });

void ConfigViewController::SetupMenuTab() {
  auto _menuTab =
      QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

  auto headerA = QuestUI::BeatSaberUI::CreateText(_menuTab->get_transform(),
                                                  "Menu Lighting", false);
  headerA->set_alignment(TMPro::TextAlignmentOptions::_get_Center());
  headerA->set_color(Color::get_gray());

  MenuConfiguration configuration =
      getColoramaConfig().menuConfiguration.GetValue();

  CPE("Gamemode Selection Menu", gamemodeLighting);
  CPE("Solo/Party Menu", freeplayLighting);
  CPE("Campaign Menu", campaignLighting);
  CPE("Multiplayer Lobby (Idle)", multiplayerIdleColor);
  CPE("Multiplayer Lobby (Countdown)", multiplayerCountdownColor);
  CPE("Results Menu (Pass)", resultsLighting);
  CPE("Results Menu (Fail)", resultsFailLighting);

  auto headerB = QuestUI::BeatSaberUI::CreateText(_menuTab->get_transform(),
                                                  "Menu Environment", false);
  headerB->set_alignment(TMPro::TextAlignmentOptions::_get_Center());
  headerB->set_color(Color::get_gray());

  auto vertGroup_menuTab =
      QuestUI::BeatSaberUI::CreateModifierContainer(_menuTab->get_transform());

  CMT("Enable Fog Ring", enableFogRing)
  CMT("Enable Menu Floor", enableFloor)
  CMT("Enable Note Decor", enableNoteDecor)
  CMT("Enable Logo Glow Lines", enableLogoGlowLines)

  this->menuTab =
      this->AdjustedScrollContainerObject(_menuTab->get_gameObject(), true);
}


