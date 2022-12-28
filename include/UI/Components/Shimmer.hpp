#pragma once

#include "Colorama.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/Gradient.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

DECLARE_CLASS_CODEGEN(Colorama::UI::Components, Shimmer,
                      UnityEngine::MonoBehaviour,
                      DECLARE_INSTANCE_METHOD(void, Update);
                      DECLARE_INSTANCE_METHOD(void, Awake);
                      DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, text);)