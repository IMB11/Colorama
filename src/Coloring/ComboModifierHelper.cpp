#include "Colorama.hpp"

#include "UnityEngine/Transform.hpp"
#include "GlobalNamespace/ComboUIController.hpp"
#include "HMUI/ImageView.hpp"

using namespace UnityEngine;
using namespace HMUI;
using namespace GlobalNamespace;

MAKE_HOOK_MATCH(ComboUIController_StartHook, &ComboUIController::Start, void, ComboUIController* self) {
  ComboUIController_StartHook(self);

  ComboConfiguration config = getColoramaConfig().comboConfiguration.GetValue();
  if(self->get_isActiveAndEnabled() && config.enabled) {
    auto fullComboLines = self->GetComponentsInChildren<ImageView*>();

    if(config.useGradient) {
      fullComboLines[0]->gradient = true;
      fullComboLines[1]->gradient = true;

      fullComboLines[0]->color0 = config.topLeft;
      fullComboLines[0]->color1 = config.topRight;

      if(config.mirrorToBottom) {
        fullComboLines[1]->color0 = config.topLeft;
        fullComboLines[1]->color1 = config.topRight;
      } else {
        fullComboLines[1]->color0 = config.bottomLeft;
        fullComboLines[1]->color1 = config.bottomRight;
      }
    } else {
      fullComboLines[0]->gradient = false;
      fullComboLines[1]->gradient = false;
      fullComboLines[0]->set_color(config.topLineColor);
      fullComboLines[1]->set_color(config.bottomLineColor);
    }
  }
}

void ComboUIControllerHooks(Logger& logger) {
  INSTALL_HOOK(logger, ComboUIController_StartHook)
}

ColoramaInstallHooks(ComboUIControllerHooks)