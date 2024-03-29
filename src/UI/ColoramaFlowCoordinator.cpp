#include "UI/ColoramaFlowCoordinator.hpp"

#include "HMUI/ViewController.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "questui/shared/BeatSaberUI.hpp"

DEFINE_TYPE(Colorama::UI, ColoramaFlowCoordinator);

using namespace Colorama::UI;
using namespace Colorama::Coloring;

void ColoramaFlowCoordinator::SetupFields(
  GlobalNamespace::MainFlowCoordinator *mainFlowCoordinator,
  InfoViewController                   *infoViewController,
  ConfigViewController                 *configViewController,
  PreviewViewController                *previewViewController) {
  this->_mainFlowCoordinator              = mainFlowCoordinator;
  this->_infoViewController               = infoViewController;
  this->_infoViewController->parentFlow = this;
  this->_configViewController             = configViewController;
  this->_configViewController->parentFlow = this;
  this->_previewViewController            = previewViewController;
}

void ColoramaFlowCoordinator::DidActivate(bool firstActivation,
                                          bool addedToHierarchy,
                                          bool screenSystemEnabling) {
  using namespace GlobalNamespace;
  using namespace HMUI;
  using namespace UnityEngine;

  LOG("DidActivate");
  if (firstActivation) {
    SetTitle("Colorama", ViewController::AnimationType::_get_In());
    showBackButton = true;
    ProvideInitialViewControllers(_configViewController,
                                  _infoViewController,
                                  _previewViewController,
                                  nullptr,
                                  nullptr);
  }
}

void ColoramaFlowCoordinator::BackButtonWasPressed(
  HMUI::ViewController *topViewController) {
  using namespace GlobalNamespace;
  using namespace HMUI;
  using namespace UnityEngine;

  getColoramaConfig().Save();
  parentFlowCoordinator->DismissFlowCoordinator(
    this, ViewController::AnimationDirection::Horizontal, nullptr, false);
}