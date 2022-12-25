#include "UI/ColoramaFlowCoordinator.hpp"

#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSMLDataCache.hpp"

using namespace Colorama::UI;

DEFINE_TYPE(Colorama::UI, ColoramaFlowCoordinator);

void ColoramaFlowCoordinator::Dispose() {

}

void ColoramaFlowCoordinator::Initialize() {
  LOG("Initialize");
  BSML::Register::RegisterMenuButton("Colorama", "Open the configuration menu for Colorama", )
}

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