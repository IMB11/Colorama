#include "ColoramaConfig.hpp"

ColorPair::operator UnityEngine::Color() const {
  return UnityEngine::Color(r / 255.0f, g / 255.0f, b / 255.0f, a);
}

ColorPair::operator bool() const {
  return enabled;
}

ConvertedColor::operator UnityEngine::Color() const {
  return UnityEngine::Color(r / 255.0f, g / 255.0f, b / 255.0f, a);
}