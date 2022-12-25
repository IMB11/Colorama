#include "UI/ColoramaFlowCoordinator.hpp"

#include "HMUI/ViewController_AnimationType.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController.hpp"

using namespace Colorama::UI;

DEFINE_TYPE(Colorama::UI, ColoramaFlowCoordinator);

void ColoramaFlowCoordinator::Dispose() {
  BSML::Register::UnRegisterMenuButton(this->_menuButton);
  this->_menuButton = nullptr;
}

void ColoramaFlowCoordinator::Inject(ListWrapper<Colorama::Coloring::Services::ColorizerService *> colorizerServices) {
  this->_colorizerServices = colorizerServices;
}

void ColoramaFlowCoordinator::Initialize() {
  LOG("Initialize");
  this->_menuButton = BSML::Register::RegisterMenuButton("Colorama", "Open the configuration menu for Colorama", [this]() {
    auto fc = QuestUI::BeatSaberUI::GetMainFlowCoordinator()->YoungestChildFlowCoordinatorOrSelf();
    fc->PresentFlowCoordinator(this, nullptr, HMUI::ViewController::AnimationDirection::Horizontal, false, false);
  });
}

void ColoramaFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
  using namespace GlobalNamespace;
  using namespace HMUI;
  using namespace UnityEngine;

  if(firstActivation) {
    this->set_showBackButton(true);
    SetTitle("Colorama", ViewController::AnimationType::_get_None());
  }
}

void ColoramaFlowCoordinator::BackButtonWasPressed(HMUI::ViewController *topViewController) {
  using namespace GlobalNamespace;
  using namespace HMUI;
  using namespace UnityEngine;
}