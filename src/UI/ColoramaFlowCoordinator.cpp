#include "UI/ColoramaFlowCoordinator.hpp"

#include "HMUI/ViewController.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "questui/shared/BeatSaberUI.hpp"

DEFINE_TYPE(Colorama::UI, ColoramaFlowCoordinator);

using namespace Colorama::UI;

void ColoramaFlowCoordinator::Construct(
    GlobalNamespace::MainFlowCoordinator *mainFlowCoordinator,
    InfoViewController *infoViewController) {
  this->_mainFlowCoordinator = mainFlowCoordinator;
  this->_infoViewController = infoViewController;
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
	ProvideInitialViewControllers(_infoViewController, nullptr, nullptr,
	                              nullptr, nullptr);
  }
}

void ColoramaFlowCoordinator::BackButtonWasPressed(
    HMUI::ViewController *topViewController) {
  using namespace GlobalNamespace;
  using namespace HMUI;
  using namespace UnityEngine;
}