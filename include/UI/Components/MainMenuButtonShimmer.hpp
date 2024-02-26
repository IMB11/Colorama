#pragma once

#include "Colorama.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/Gradient.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

DECLARE_CLASS_CODEGEN(Colorama::UI::Components, MainMenuButtonShimmer,
                      UnityEngine::MonoBehaviour,
                      DECLARE_INSTANCE_FIELD_DEFAULT(bool, disableTextFetch, false);
                      DECLARE_INSTANCE_METHOD(void, Update);
                      DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, btn);)