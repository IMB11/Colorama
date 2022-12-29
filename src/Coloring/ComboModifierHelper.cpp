#include "Coloring/ComboModifierHelper.hpp"

#include "UnityEngine/Transform.hpp"
#include "HMUI/ImageView.hpp"

DEFINE_TYPE(Colorama::Coloring, ComboModifierHelper)

using namespace Colorama::Coloring;
using namespace UnityEngine;
using namespace HMUI;
using namespace GlobalNamespace;

void ComboModifierHelper::HelperSetup(ComboUIController *comboUIController) {
  this->_comboUIController = comboUIController;
  this->get_transform()->SetParent(this->_comboUIController->get_transform());
  this->ModPanel();
}

void ComboModifierHelper::ModPanel() {
  ComboConfiguration config = getColoramaConfig().comboConfiguration.GetValue();

  if(this->_comboUIController->get_isActiveAndEnabled() && config.enabled) {
	auto fullComboLines = this->_comboUIController->GetComponentsInChildren<ImageView*>();

	if(config.useGradient) {
	  fullComboLines[0]->gradient = true;
	  fullComboLines[1]->gradient = true;

	  fullComboLines[0]->color0 = config.topLeft;
	  fullComboLines[0]->color1 = config.topRight;

	  if(config.mirrorToBottom) {
		fullComboLines[1]->color0 = config.topLeft;
		fullComboLines[1]->color1 = config.topRight;
	  } else {
		fullComboLines[1]->color0 = config.bottomLeft;
		fullComboLines[1]->color1 = config.bottomRight;
	  }
	} else {
	  fullComboLines[0]->gradient = false;
	  fullComboLines[1]->gradient = false;
	  fullComboLines[0]->set_color(config.topLineColor);
	  fullComboLines[1]->set_color(config.bottomLineColor);
	}
  }
}

void ComboModifierHelper::OnDestroy() {
  this->_comboUIController = nullptr;
}