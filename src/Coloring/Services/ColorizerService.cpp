#include "Coloring/Services/ColorizerService.hpp"

DEFINE_TYPE(Colorama::Coloring::Services, ColorizerService)

using namespace Colorama::Coloring::Services;

void ColorizerService::ctor(Tweening::TimeTweeningManager*timeTweeningManager) {
  this->_tweeningManager = timeTweeningManager;
  this->set_v_color(this->get_v_relatedValue().get().GetValue());
}