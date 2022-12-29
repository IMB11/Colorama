#pragma once

#include <string>

#include "Colorama.hpp"
#include "UnityEngine/Color.hpp"
#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"
#include "config-utils/shared/config-utils.hpp"

using namespace UnityEngine;

DECLARE_JSON_CLASS(
    ColorPair,
    NAMED_VALUE_DEFAULT(float, r, 255.0f, "r");
    NAMED_VALUE_DEFAULT(float, g, 0.0, "g");
    NAMED_VALUE_DEFAULT(float, b, 0.0f, "b");
    NAMED_VALUE_DEFAULT(float, a, 1.0f, "a");
    NAMED_VALUE_DEFAULT(bool, enabled, false, "enabled");
    static UnityEngine::Color convert(ColorPair pair) {
      return UnityEngine::Color(pair.r / 255.0f, pair.g / 255.0f, pair.b / 255.0f, pair.a);
    }
    static ColorPair convert(UnityEngine::Color color, bool enabled) {
      ColorPair pair = {};
      pair.r = color.r * 255.0f;
      pair.g = color.g * 255.0f;
      pair.b = color.b * 255.0f;
      pair.a = color.a;
      pair.enabled = enabled;
      return pair;
    };)

DECLARE_JSON_CLASS(MenuConfiguration,
                   NAMED_VALUE_DEFAULT(ColorPair, gamemodeLighting, {}, "gamemodeLighting");
                   NAMED_VALUE_DEFAULT(ColorPair, freeplayLighting, {}, "freeplayLighting");
                   NAMED_VALUE_DEFAULT(ColorPair, campaignLighting, {}, "campaignLighting");
                   NAMED_VALUE_DEFAULT(ColorPair, multiplayerIdleColor, {}, "multiplayerIdleColor");
                   NAMED_VALUE_DEFAULT(ColorPair, multiplayerCountdownColor, {}, "multiplayerCountdownColor");
                   NAMED_VALUE_DEFAULT(ColorPair, resultsLighting, {}, "resultsLighting");
                   NAMED_VALUE_DEFAULT(ColorPair, resultsFailLighting, {}, "resultsFailLighting");
                   NAMED_VALUE_DEFAULT(ColorPair, feetColor, {}, "feetColor");
                   NAMED_VALUE_DEFAULT(bool, enableFogRing, true, "enableFogRing");
                   NAMED_VALUE_DEFAULT(bool, enableNoteDecor, true, "enableNoteDecor");
                   NAMED_VALUE_DEFAULT(bool, enableLogoGlowLines, true, "enableLogoGlowLines");
                   NAMED_VALUE_DEFAULT(bool, enableFloor, true, "enableFloor"));

DECLARE_CONFIG(ColoramaConfig,
               CONFIG_VALUE(menuConfiguration, MenuConfiguration,
                            "Menu Configuration Tab", {});)
