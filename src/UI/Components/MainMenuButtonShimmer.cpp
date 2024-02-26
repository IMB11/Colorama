#include "UI/Components/MainMenuButtonShimmer.hpp"

#include "UnityEngine/Mathf.hpp"
#include "UnityEngine/Time.hpp"
#include "UnityEngine/UI/Text.hpp"

DEFINE_TYPE(Colorama::UI::Components, MainMenuButtonShimmer);

using namespace Colorama::UI::Components;

namespace ShimmerUtils2 {
  float repeat(float t, float length = 1.0F) {
    return std::clamp(t - std::floor(t / length) * length, 0.0f, length);
  }

  float pingPong(float t, float length = 1.0F) {
    t = repeat(t, length * 2.0F);
    return length - std::abs(t - length);
  }
}

void MainMenuButtonShimmer::Update() {
  if(btn) {
    auto txt = btn->GetComponentInChildren<TMPro::TextMeshProUGUI*>();

    if(txt) {
      txt->set_color(Color::HSVToRGB(ShimmerUtils2::pingPong(Time::get_time() * 0.25f, 1), 1, 1));
    }
  }
}