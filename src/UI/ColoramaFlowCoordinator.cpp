#include "UI/ColoramaFlowCoordinator.hpp"

#include "HMUI/ViewController_AnimationType.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController.hpp"

#include "questui/shared/BeatSaberUI.hpp"

using namespace Colorama::UI;

DEFINE_TYPE(Colorama::UI, ColoramaFlowCoordinator);

static SafePtrUnity<ColoramaFlowCoordinator> _instance;

void ColoramaFlowCoordinator::Dispose() {
  _instance = nullptr;
}

void ColoramaFlowCoordinator::Inject(ListWrapper<Colorama::Coloring::Services::ColorizerService *> colorizerServices) {
  this->_colorizerServices = colorizerServices;
  _instance = this;
}

void ColoramaFlowCoordinator::Initialize() {
  LOG("Initialize");
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