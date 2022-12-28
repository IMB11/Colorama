#include "UI/Components/Shimmer.hpp"

#include "UnityEngine/Mathf.hpp"
#include "UnityEngine/Time.hpp"
#include "custom-types/shared/coroutine.hpp"

DEFINE_TYPE(Colorama::UI::Components, Shimmer);

using namespace Colorama::UI::Components;

void Shimmer::Awake() { text = GetComponent<TMPro::TextMeshProUGUI *>(); }

float pingPong(float t, float length) {
  t = UnityEngine::Mathf::Repeat(t, length * 2.0f);
  return length - std::abs(t - length);
}

void Shimmer::Update() {
  text->set_color(Color::HSVToRGB(pingPong(Time::get_time() * 0.25f, 1), 1, 1));
}