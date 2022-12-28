#pragma once

#include <string>

#include "Colorama.hpp"
#include "UnityEngine/Color.hpp"
#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"
#include "config-utils/shared/config-utils.hpp"

using namespace UnityEngine;

#define ENABLE_COLOR_CONFIG_VALUE(name, desc)        \
  CONFIG_VALUE(Can_##name, bool, "Can" desc, false); \
  CONFIG_VALUE(name, ConfigUtils::Color, desc,       \
               static_cast<ConfigUtils::Color>(Color::get_red()));

DECLARE_JSON_CLASS(
    ColorPair,
    VALUE_DEFAULT(float, r, 255.0f);
    VALUE_DEFAULT(float, g, 0.0);
    VALUE_DEFAULT(float, b, 0.0f);
    VALUE_DEFAULT(float, a, 0.0f);
    VALUE_DEFAULT(bool, enabled, false);
    operator UnityEngine::Color() const;
    static ColorPair convert(UnityEngine::Color color, bool enabled) {
      ColorPair pair = {};
      pair.r = color.r * 255.0f;
      pair.g = color.g * 255.0f;
      pair.b = color.b * 255.0f;
      pair.a = color.a * 255.0f;
      pair.enabled = enabled;
      return pair;
    };)

DECLARE_JSON_CLASS()

DECLARE_JSON_CLASS(MenuConfiguration,
                   VALUE_DEFAULT(ColorPair, gamemodeLighting, {});
                   VALUE_DEFAULT(ColorPair, freeplayLighting, {});
                   VALUE_DEFAULT(ColorPair, campaignLighting, {});
                   VALUE_DEFAULT(ColorPair, multiplayerIdleColor, {});
                   VALUE_DEFAULT(ColorPair, multiplayerCountdownColor, {})
                       VALUE_DEFAULT(ColorPair, resultsLighting, {});
                   VALUE_DEFAULT(ColorPair, resultsFailLighting, {});
                   VALUE_DEFAULT(ColorPair, feetColor, {});
                   VALUE_DEFAULT(bool, enableFogRing, true);
                   VALUE_DEFAULT(bool, enableNoteDecor, true);
                   VALUE_DEFAULT(bool, enableLogoGlowLines, true);
                   VALUE_DEFAULT(bool, enableFloor, true);)

DECLARE_CONFIG(ColoramaConfig,
               CONFIG_VALUE(menuConfiguration, MenuConfiguration,
                            "Menu Configuration Tab", {});)
