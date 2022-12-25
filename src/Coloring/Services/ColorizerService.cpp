#include "Coloring/Services/ColorizerService.hpp"

DEFINE_TYPE(Colorama::Coloring::Services, ColorizerService)

using namespace Colorama::Coloring::Services;

void ColorizerService::ctor(Tweening::TimeTweeningManager* _tweeningManager) {
  this->_tweeningManager = _tweeningManager;
}