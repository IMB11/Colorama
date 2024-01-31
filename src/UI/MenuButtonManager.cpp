#include "UI/MenuButtonManager.hpp"

#include "HMUI/ViewController_AnimationDirection.hpp"

DEFINE_TYPE(Colorama::UI, MenuButtonManager);

using namespace Colorama::UI;

void MenuButtonManager::SummonModFlowCoordinator() {
  _mainFlowCoordinator->YoungestChildFlowCoordinatorOrSelf()->PresentFlowCoordinator(
      this->_modFlowCoordinator, nullptr,
      HMUI::ViewController::AnimationDirection::_get_Vertical(), false, false);
}

void MenuButtonManager::ctor(GlobalNamespace::MainFlowCoordinator *mfc,
                               ColoramaFlowCoordinator *mofc, InfoViewController *infoViewController, ConfigViewController *configViewController, PreviewViewController* previewViewController) {
  mofc->SetupFields(mfc, infoViewController, configViewController, previewViewController);
  this->_mainFlowCoordinator = mfc;
  this->_menuButton = BSML::MenuButton::Make_new(
      "Colorama", "Open Colorama's configuration screen.",
      std::bind(&MenuButtonManager::SummonModFlowCoordinator, this));
  this->_modFlowCoordinator = mofc;

  INFO("Instantiated MenuButtonManager")
}

void MenuButtonManager::Initialize() {
  BSML::Register::RegisterMenuButton(this->_menuButton);
}

void MenuButtonManager::Dispose() {
  BSML::Register::UnRegisterMenuButton(this->_menuButton);
}