#include "UI/ColoramaFlowCoordinator.hpp"

using namespace Colorama::UI;

DEFINE_TYPE(Colorama::UI, ColoramaFlowCoordinator);

void ColoramaFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
  using namespace GlobalNamespace;
  using namespace HMUI;
  using namespace UnityEngine;

  if(firstActivation) {
    this->set_showBackButton(true);
    SetTitle("Colorama");
  }
}

void ColoramaFlowCoordinator::BackButtonWasPressed(HMUI::ViewController *topViewController) {
  using namespace GlobalNamespace;
  using namespace HMUI;
  using namespace UnityEngine;
}