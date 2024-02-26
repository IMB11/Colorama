#pragma once

#include <string>

#include "Colorama.hpp"
#include "UnityEngine/Color.hpp"
#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"
#include "config-utils/shared/config-utils.hpp"

using namespace UnityEngine;

DECLARE_JSON_CLASS(
  ColorPair, NAMED_VALUE_DEFAULT(float, r, 255.0f, "r");
  NAMED_VALUE_DEFAULT(float, g, 0.0, "g");
  NAMED_VALUE_DEFAULT(float, b, 0.0f, "b");
  NAMED_VALUE_DEFAULT(float, a, 1.0f, "a");
  NAMED_VALUE_DEFAULT(bool, enabled, false, "enabled");
  operator UnityEngine::Color() const;
  operator bool() const;

  static ColorPair convert(UnityEngine::Color color, bool enabled) {
    ColorPair pair = {};
    pair.r         = color.r * 255.0f;
    pair.g         = color.g * 255.0f;
    pair.b         = color.b * 255.0f;
    pair.a         = color.a;
    pair.enabled   = enabled;
    return pair;
  };)

DECLARE_JSON_CLASS(
  ConvertedColor, NAMED_VALUE_DEFAULT(float, r, 255.0f, "r");
  NAMED_VALUE_DEFAULT(float, g, 0.0, "g");
  NAMED_VALUE_DEFAULT(float, b, 0.0f, "b");
  NAMED_VALUE_DEFAULT(float, a, 1.0f, "a");
  operator UnityEngine::Color() const;
  static ConvertedColor convert(UnityEngine::Color color) {
    ConvertedColor col = {};
    col.r              = color.r * 255.0f;
    col.g              = color.g * 255.0f;
    col.b              = color.b * 255.0f;
    col.a              = color.a;
    return col;
  };)

DECLARE_JSON_CLASS(
  ComboConfiguration, NAMED_VALUE_DEFAULT(bool, enabled, false, "enabled");
  NAMED_VALUE_DEFAULT(ConvertedColor, topLineColor, {}, "topLineColor");
  NAMED_VALUE_DEFAULT(ConvertedColor, bottomLineColor, {}, "bottomLineColor");

  NAMED_VALUE_DEFAULT(bool, useGradient, false, "useGradient");
  NAMED_VALUE_DEFAULT(bool, mirrorToBottom, false, "gradient_mirrorToBottom");
  NAMED_VALUE_DEFAULT(ConvertedColor, topLeft, {}, "gradient_topLeft");
  NAMED_VALUE_DEFAULT(ConvertedColor, topRight, {}, "gradient_topRight");
  NAMED_VALUE_DEFAULT(ConvertedColor, bottomLeft, {}, "gradient_bottomLeft");
  NAMED_VALUE_DEFAULT(ConvertedColor, bottomRight, {}, "gradient_bottomRight");)

DECLARE_JSON_CLASS(
  EnergyBarConfiguration, NAMED_VALUE_DEFAULT(bool, enabled, false, "enabled");
  NAMED_VALUE_DEFAULT(bool, rainbowFull, false, "rainbowFull");

  NAMED_VALUE_DEFAULT(ConvertedColor, lowColor, {}, "lowColor");
  NAMED_VALUE_DEFAULT(ConvertedColor, midColor, {}, "midColor");
  NAMED_VALUE_DEFAULT(ConvertedColor, highColor, {}, "highColor");)

DECLARE_JSON_CLASS(
  MenuConfiguration,
  NAMED_VALUE_DEFAULT(ColorPair, gamemodeLighting, {}, "gamemodeLighting");
  NAMED_VALUE_DEFAULT(ColorPair, freeplayLighting, {}, "freeplayLighting");
  NAMED_VALUE_DEFAULT(ColorPair, campaignLighting, {}, "campaignLighting");
  NAMED_VALUE_DEFAULT(
    ColorPair, multiplayerIdleColor, {}, "multiplayerIdleColor");
  NAMED_VALUE_DEFAULT(
    ColorPair, multiplayerCountdownColor, {}, "multiplayerCountdownColor");
  NAMED_VALUE_DEFAULT(ColorPair, resultsLighting, {}, "resultsLighting");
  NAMED_VALUE_DEFAULT(
    ColorPair, resultsFailLighting, {}, "resultsFailLighting");
  NAMED_VALUE_DEFAULT(ColorPair, feetColor, {}, "feetColor");
  NAMED_VALUE_DEFAULT(bool, enableFogRing, true, "enableFogRing");
  NAMED_VALUE_DEFAULT(bool, enableNoteDecor, true, "enableNoteDecor");
  NAMED_VALUE_DEFAULT(bool, enableLogoGlowLines, true, "enableLogoGlowLines");
  NAMED_VALUE_DEFAULT(bool, enableFloor, true, "enableFloor");)

DECLARE_JSON_CLASS(
  ProgressBarConfiguration,
  NAMED_VALUE_DEFAULT(bool, enabled, false, "enabled");
  NAMED_VALUE_DEFAULT(bool, enableGradient, false, "enableGradient");
  NAMED_VALUE_DEFAULT(ConvertedColor, fillColor, {}, "fillColor");
  NAMED_VALUE_DEFAULT(ConvertedColor, handleColor, {}, "handleColor");
  NAMED_VALUE_DEFAULT(ConvertedColor, bgColor, {}, "bgColor");
  NAMED_VALUE_DEFAULT(ConvertedColor, startColor, {}, "startColor");
  NAMED_VALUE_DEFAULT(ConvertedColor, endColor, {}, "endColor");)

DECLARE_JSON_CLASS(
  MultiplierConfig, NAMED_VALUE_DEFAULT(bool, enabled, true, "enabled");
  NAMED_VALUE_DEFAULT(bool, enableRainbow, true, "enableRainbow");
  NAMED_VALUE_DEFAULT(ConvertedColor, oneColor, {}, "oneColor");
  NAMED_VALUE_DEFAULT(ConvertedColor, twoColor, {}, "twoColor");
  NAMED_VALUE_DEFAULT(ConvertedColor, fourColor, {}, "fourColor");
  NAMED_VALUE_DEFAULT(ConvertedColor, eightColor, {}, "eightColor");)

DECLARE_CONFIG(ColoramaConfig,
               CONFIG_VALUE(progressBarConfiguration,
                            ProgressBarConfiguration,
                            "Progress Bar Configuration",
                            {});
               CONFIG_VALUE(energyBarConfiguration,
                            EnergyBarConfiguration,
                            "Energy Configuration Tab",
                            {});
               CONFIG_VALUE(comboConfiguration,
                            ComboConfiguration,
                            "Combo Configuration Tab",
                            {});
               CONFIG_VALUE(multiplierConfiguration,
                            MultiplierConfig,
                            "Multiplier Configuration Tab",
                            {});
               CONFIG_VALUE(menuConfiguration,
                            MenuConfiguration,
                            "Menu Configuration Tab",
                            {});)
