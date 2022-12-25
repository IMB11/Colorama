#pragma once

#include "Colorama.hpp"
#include "Coloring/ColorUtils.hpp"
#include "Coloring/Services/ColorizerService.hpp"

#include "GlobalNamespace/MenuLightsManager.hpp"
#include "Tweening/Tween.hpp"
#include "Tweening/TweeningManager.hpp"

DECLARE_CLASS_CODEGEN(Colorama::Coloring::Services, DefaultMenuService, Colorama::Coloring::Services::ColorizerService,
                  DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::MenuLightsManager*, _lightsManager);
                  DECLARE_INSTANCE_FIELD_PRIVATE(Tweening::Tween*, _tween);
                  DECLARE_CTOR(ctor, GlobalNamespace::MenuLightsManager* _lightsManager, Tweening::Tween* _tween);
                  public:
                      void set_v_color(UnityEngine::Color color);
                      UnityEngine::Color get_v_color();
                      StringW get_v_name();
                      void SetColor(UnityEngine::Color color);
)