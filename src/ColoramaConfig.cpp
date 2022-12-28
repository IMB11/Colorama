#include "ColoramaConfig.hpp"

#include "UnityEngine/Color.hpp"

ColorPair::operator UnityEngine::Color() const {
  return UnityEngine::Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}