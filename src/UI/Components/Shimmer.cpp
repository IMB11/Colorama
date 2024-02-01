#include "UI/Components/Shimmer.hpp"

#include "UnityEngine/Mathf.hpp"
#include "UnityEngine/Time.hpp"
#include "custom-types/shared/coroutine.hpp"

DEFINE_TYPE(Colorama::UI::Components, Shimmer);

using namespace Colorama::UI::Components;

namespace ShimmerUtils {
  float repeat(float t, float length = 1.0F) {
    return std::clamp(t - std::floor(t / length) * length, 0.0f, length);
  }

  float pingPong(float t, float length = 1.0F) {
    t = repeat(t, length * 2.0F);
    return length - std::abs(t - length);
  }
}

void Shimmer::Awake() { text = GetComponent<TMPro::TextMeshProUGUI *>(); }

void Shimmer::Update() {

  text->set_color(Color::HSVToRGB(ShimmerUtils::pingPong(Time::get_time() * 0.25f, 1), 1, 1));
}