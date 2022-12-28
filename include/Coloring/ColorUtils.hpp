#pragma once

#include <map>

#include "Colorama.hpp"
#include "GlobalNamespace/ColorSO.hpp"
#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "GlobalNamespace/MenuLightsManager.hpp"
#include "GlobalNamespace/MenuLightsPresetSO.hpp"
#include "GlobalNamespace/MenuLightsPresetSO_LightIdColorPair.hpp"
#include "GlobalNamespace/SimpleColorSO.hpp"
#include "UnityEngine/ScriptableObject.hpp"
#include "UnityEngine/SpriteRenderer.hpp"

namespace Colorama::Coloring::Utils {
GlobalNamespace::ColorSO *createColorSO(Color color) {
  float t = color.r + color.g + color.b;
  auto so =
      ScriptableObject::CreateInstance<GlobalNamespace::SimpleColorSO *>();
  so->color = color;
  return so;
}

GlobalNamespace::MenuLightsPresetSO *createMenuLights(
    GlobalNamespace::MenuLightsPresetSO *defaultLights, Color color) {
  float t = color.r + color.g + color.b;
  auto colorSO = createColorSO(color);
  auto menuPresetSO = Object::Instantiate(defaultLights);
  auto colorPairs = menuPresetSO->lightIdColorPairs;
  for (int i = 0; i < colorPairs.Length(); ++i) {
	auto pair =
	    GlobalNamespace::MenuLightsPresetSO::LightIdColorPair::New_ctor();
	pair->lightId = colorPairs[i]->lightId;
	pair->baseColor = colorSO;
	pair->intensity = colorPairs[i]->intensity;
	colorPairs[i] = pair;
  }
  return menuPresetSO;
}
}  // namespace Colorama::Coloring::Utils