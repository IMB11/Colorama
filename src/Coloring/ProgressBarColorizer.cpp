#include "Coloring/ProgressBarColorizer.hpp"

#include "UnityEngine/UI/Image.hpp"

DEFINE_TYPE(Colorama::Coloring, ProgressBarColorizer);

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace Colorama::Coloring;

void ProgressBarColorizer::Construct(
    SongProgressUIController* progressUIController,
    IAudioTimeSource* audioTimeSyncController) {
  this->progressUIController = progressUIController;
  this->audioTimeSyncController = audioTimeSyncController;
}

void ProgressBarColorizer::Start() {
  ProgressBarConfiguration config = getColoramaConfig().progressBarConfiguration.GetValue();
  if(!config.enabled) return;

  for (UI::Image* img : progressUIController->get_transform()->GetComponentsInChildren<UI::Image*>()) {
    if (img->get_name() != "BG") {
      // [0] Progress, [1] Background, [2] Handle
      barComponents.push_back(img);
    }
  }

  if (!config.enableGradient) {
    barComponents[0]->set_color(config.fillColor);
  }

  Color colorWithAlpha = Color(config.bgColor.r, config.bgColor.g, config.bgColor.b, 0.25F);
  barComponents[1]->set_color(colorWithAlpha);
  barComponents[2]->set_color(config.handleColor);
}

void ProgressBarColorizer::Update() {
  ProgressBarConfiguration config = getColoramaConfig().progressBarConfiguration.GetValue();
  if(!config.enabled) return;

  if(config.enableGradient && barComponents.size() > 1) {
    barComponents[0]->set_color(Color::Lerp(config.startColor, config.endColor, audioTimeSyncController->get_songTime() / audioTimeSyncController->get_songLength()));
  }
}

MAKE_HOOK_MATCH(SongProgressUIController_StartHook, &SongProgressUIController::Start, void, SongProgressUIController* self) {
  SongProgressUIController_StartHook(self);

  ProgressBarConfiguration config = getColoramaConfig().progressBarConfiguration.GetValue();

  if(config.enabled) {
    self->get_gameObject()->AddComponent<ProgressBarColorizer*>()->Construct(self, self->audioTimeSource);
  }


}


