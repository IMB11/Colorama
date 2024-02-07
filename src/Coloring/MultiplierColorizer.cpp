#include "Colorama.hpp"

#include "GlobalNamespace/ScoreMultiplierUIController.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "UnityEngine/Time.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace HMUI;

namespace MultiplierUtils {
float repeat(float t, float length = 1.0F) {
  return std::clamp(t - std::floor(t / length) * length, 0.0f, length);
}

float pingPong(float t, float length = 1.0F) {
  t = repeat(t, length * 2.0F);
  return length - std::abs(t - length);
}
}


MAKE_HOOK_MATCH(ScoreMultiplierUIController_UpdateHook, &ScoreMultiplierUIController::Update, void, ScoreMultiplierUIController* self) {
  ScoreMultiplierUIController_UpdateHook(self);

  auto texts = self->get_transform()->Find("TextPanel")->GetComponentsInChildren<CurvedTextMeshPro*>();
  auto bg = self->get_transform()->Find("BGCircle")->GetComponent<UI::Image*>();
  auto fg = self->get_transform()->Find("FGCircle")->GetComponent<UI::Image*>();

  MultiplierConfig config = getColoramaConfig().multiplierConfiguration.GetValue();

  if(config.enabled && self->get_isActiveAndEnabled()) {
#define WITH_ALPHA(color) Color(color.r, color.g, color.b, 0.25f)
    if(texts[1]->get_text() == "1") {
      bg->set_color(WITH_ALPHA(config.oneColor));
      fg->set_color(config.oneColor);
    } else if(texts[1]->get_text() == "2") {
      bg->set_color(WITH_ALPHA(config.twoColor));
      fg->set_color(config.twoColor);
    } else if(texts[1]->get_text() == "4") {
      bg->set_color(WITH_ALPHA(config.fourColor));
      fg->set_color(config.fourColor);
    } else if(texts[1]->get_text() == "8") {
      if(config.enableRainbow) {
        bg->set_color(Color::HSVToRGB(
            MultiplierUtils::pingPong(Time::get_time() * .5f, 1), 1, 1));
      } else {
        bg->set_color(config.eightColor);
      }
    }
  }
}

void InstallMultiplierHooks(Logger& logger) {
  INSTALL_HOOK(logger, ScoreMultiplierUIController_UpdateHook);
}

ColoramaInstallHooks(InstallMultiplierHooks)