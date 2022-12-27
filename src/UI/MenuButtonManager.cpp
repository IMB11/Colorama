#include "UI/MenuButtonManager.hpp"

#include "HMUI/ViewController_AnimationDirection.hpp"

DEFINE_TYPE(Colorama::UI, MenuButtonManager);

using namespace Colorama::UI;

void MenuButtonManager::ctor(GlobalNamespace::MainFlowCoordinator *mfc, ColoramaFlowCoordinator *mofc) {
  this->_mainFlowCoordinator = mfc;
  this->_modFlowCoordinator = mofc;
  this->_menuButton = BSML::MenuButton::Make_new("Colorama", "Open Colorama's configuration screen.", [this] { SummonModFlowCoordinator(); });

  LOG(_mainFlowCoordinator == nullptr ? "no" : "yes");
  LOG(_modFlowCoordinator == nullptr ? "no" : "yes");
}

void MenuButtonManager::SummonModFlowCoordinator() {
  this->_mainFlowCoordinator->PresentFlowCoordinator(this->_modFlowCoordinator, nullptr, HMUI::ViewController::AnimationDirection::_get_Vertical(), false, false);
}

//void MenuButtonManager::Inject(GlobalNamespace::MainFlowCoordinator *mfc, ColoramaFlowCoordinator *mofc) {
//  this->_mainFlowCoordinator = mfc;
//  this->_modFlowCoordinator = mofc;
//}

void MenuButtonManager::Initialize() {
  BSML::Register::RegisterMenuButton(this->_menuButton);
}

void MenuButtonManager::Dispose() {
  BSML::Register::UnRegisterMenuButton(this->_menuButton);
}