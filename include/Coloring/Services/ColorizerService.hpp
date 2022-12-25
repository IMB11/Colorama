#pragma once

#include "Colorama.hpp"

#include "Tweening/TimeTweeningManager.hpp"

DECLARE_CLASS_CODEGEN(Colorama::Coloring::Services, ColorizerService, Il2CppObject,
                      DECLARE_INSTANCE_FIELD(Tweening::TimeTweeningManager*, _tweeningManager);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Color, _color);
                      DECLARE_CTOR(ctor, Tweening::TimeTweeningManager* _tweeningManager);
                      public:
                        virtual void set_v_color(UnityEngine::Color color) = 0;
                        virtual UnityEngine::Color get_v_color() = 0;
                        virtual StringW get_v_name() = 0;
                        virtual std::reference_wrapper<ConfigUtils::ConfigValue<ConfigUtils::Color>> get_v_relatedValue() = 0;
                        const int MENU_LIGHT_ID = 1;
)