#include "UI/MenuButtonManager.hpp"

#include <UnityEngine/WaitForSecondsRealtime.hpp>

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "UI/Components/MainMenuButtonShimmer.hpp"
#include "UI/Components/Shimmer.hpp"
#include "custom-types/shared/coroutine.hpp"

DEFINE_TYPE(Colorama::UI, MenuButtonManager);

using namespace Colorama::UI;

static SafePtr<BSML::MenuButton> MenuButtonStat;

void MenuButtonManager::SummonModFlowCoordinator() {
  _mainFlowCoordinator->YoungestChildFlowCoordinatorOrSelf()
      ->PresentFlowCoordinator(
          this->_modFlowCoordinator, nullptr,
          HMUI::ViewController::AnimationDirection::_get_Vertical(), false,
          false);
}

void MenuButtonManager::ctor(GlobalNamespace::MainFlowCoordinator *mfc,
                             ColoramaFlowCoordinator *mofc,
                             InfoViewController *infoViewController,
                             ConfigViewController *configViewController,
                             PreviewViewController *previewViewController) {
  mofc->SetupFields(mfc, infoViewController, configViewController,
                    previewViewController);
  this->_mainFlowCoordinator = mfc;
  this->_menuButton = BSML::MenuButton::Make_new(
      "Colorama", "Open Colorama's configuration screen.",
      std::bind(&MenuButtonManager::SummonModFlowCoordinator, this));
  MenuButtonStat = _menuButton;

  this->_modFlowCoordinator = mofc;

  INFO("Instantiated MenuButtonManager")
}

custom_types::Helpers::Coroutine coroHook() {
  while(MenuButtonStat->menuButton == nullptr) {
    co_yield nullptr;
  }

  auto* shimmerer = MenuButtonStat->menuButton->get_gameObject()->AddComponent<Components::MainMenuButtonShimmer*>();
  shimmerer->btn = MenuButtonStat->menuButton;
}

MAKE_HOOK_MATCH(MBM_SHIMMER, &MainFlowCoordinator::DidActivate, void, MainFlowCoordinator* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
  MBM_SHIMMER(self, firstActivation, addedToHierarchy, screenSystemEnabling);

  self->StartCoroutine(custom_types::Helpers::CoroutineHelper::New(coroHook));
}

void installHook(Logger& logger) {
  INSTALL_HOOK(logger, MBM_SHIMMER);
}

ColoramaInstallHooks(installHook)

void MenuButtonManager::Initialize() {
  BSML::Register::RegisterMenuButton(this->_menuButton);
}

void MenuButtonManager::Dispose() {
  BSML::Register::UnRegisterMenuButton(this->_menuButton);
}