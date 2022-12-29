#include "UI/Views/PreviewViewController.hpp"

DEFINE_TYPE(Colorama::UI, PreviewViewController)

using namespace Colorama::UI;
using namespace Colorama::Utilities;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace QuestUI;
using namespace HMUI;

void PreviewViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
	auto grabber = GameObject::Find("ColoramaPreviewGrabber");

    if(firstActivation && !grabber) {
	  grabber = GameObject::New_ctor("ColoramaPreviewGrabber");
	  grabber->get_transform()->set_position(DEFAULT_GRABBER_POS);
	  grabber->get_transform()->Rotate(0, 57, 0);
	  objectGrabber = grabber->AddComponent<SettingsPanelObjectGrabber*>();
	  StartCoroutine(custom_types::Helpers::CoroutineHelper::New(FinalizePanels()));
    }

    StartCoroutine(custom_types::Helpers::CoroutineHelper::New(MultiplierPreviewCoroutine()));
    grabber->get_transform()->set_position(DEFAULT_GRABBER_POS);

    if(firstActivation) {
	  auto vertLayout = BeatSaberUI::CreateVerticalLayoutGroup(get_transform());
	  vertLayout->set_childControlHeight(false);
	  vertLayout->set_spacing(3);
	  vertLayout->get_rectTransform()->set_anchoredPosition({0, 30});

	  auto headerText = BeatSaberUI::CreateText(vertLayout->get_transform(), "Preview");
	  headerText->set_fontSize(18);
	  headerText->set_alignment(TMPro::TextAlignmentOptions::_get_Center());
	  headerText->set_color(Color::get_gray());
    }
}

void PreviewViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {
	objectGrabber->get_transform()->set_position(VOID_VECT3);
}

int random(int min, int max)
{
  return min + rand() % (( max + 1 ) - min);
}

void PreviewViewController::UpdatePanelVisibility(int idx) {
	if(!objectGrabber->isCompleted) return;
	auto host = objectGrabber;

    currentTab = idx;

    ///
    // [0] "Menu"
    // [1] "Energy Bar"
    // [2] "Multiplier Ring"
    // [3] "Progress Bar"
    // [4] "Combo Indicator"
    // TODO: [5] "Italics"
    ///

    switch (idx) {
	  case 0:
	    host->multiplierPanel->get_transform()->set_localPosition(VOID_VECT3);
	    host->energyPanel->SetActive(false);
	    host->comboPanel->SetActive(false);
	    host->progressPanel->SetActive(false);
	    host->immediateRankPanel->SetActive(false);
	    break;
	  case 1:
	    host->multiplierPanel->get_transform()->set_localPosition(VOID_VECT3);
	    host->energyPanel->SetActive(true);
	    host->comboPanel->SetActive(false);
	    host->progressPanel->SetActive(false);
	    host->immediateRankPanel->SetActive(false);
	    break;
	  case 2:
	    host->multiplierPanel->get_transform()->set_localPosition(Vector3::get_zero());
	    host->energyPanel->SetActive(false);
	    host->comboPanel->SetActive(false);
	    host->progressPanel->SetActive(false);
	    host->immediateRankPanel->SetActive(false);
	    break;
	  case 3:
	    host->multiplierPanel->get_transform()->set_localPosition(VOID_VECT3);
	    host->energyPanel->SetActive(false);
	    host->comboPanel->SetActive(false);
	    host->progressPanel->SetActive(true);
	    host->immediateRankPanel->SetActive(false);
	    break;
	  case 4:
	    host->multiplierPanel->get_transform()->set_localPosition(VOID_VECT3);
	    host->energyPanel->SetActive(false);
	    host->comboPanel->SetActive(true);
	    host->progressPanel->SetActive(false);
	    host->immediateRankPanel->SetActive(false);

	    numText->set_text(std::to_string(random(0, 250)));
	    host->comboPanel->get_transform()->set_localPosition(Vector3::get_zero());
	    break;
	  case 5:
	    // TODO: Italics Options
	    break;
	  default:
	    break;
    }
}

void PreviewViewController::Update() {
	if(!objectGrabber->isCompleted) return;

    ///
    // [0] "Menu"
    // [1] "Energy Bar"
    // [2] "Multiplier Ring"
    // [3] "Progress Bar"
    // [4] "Combo Indicator"
    ///

    switch(currentTab) {
	  case 1:
	    UpdateEnergyBar(fillAmount);
	    // TODO: Rainbow On Max Config
	    break;
	  case 2:
	    // TODO: Multiplier Rainbow On Max Config
		break;
	  case 3:
	    // TODO: Progress Bar Config
	    break;
	  case 4:
	    UpdateComboPanel();
//	    UpdateImmediateRankPanel(); TODO: Italic Options?
    }
}

void PreviewViewController::UpdateComboPanel() {
  ComboConfiguration config = getColoramaConfig().comboConfiguration.GetValue();

  if(config.useGradient) {
	comboLines[0]->gradient = true;
	comboLines[1]->gradient = true;
	
	comboLines[0]->color0 = config.topLeft;
	comboLines[0]->color1 = config.topRight;

	if(config.mirrorToBottom) {
	  comboLines[1]->color0 = config.topLeft;
	  comboLines[1]->color1 = config.topRight;
	} else {
	  comboLines[1]->color0 = config.bottomLeft;
	  comboLines[1]->color1 = config.bottomRight;
	}
  } else {
	comboLines[0]->gradient = false;
	comboLines[1]->gradient = false;
	comboLines[0]->set_color(config.topLineColor);
	comboLines[1]->set_color(config.bottomLineColor);
  }
}

void PreviewViewController::UpdateImmediateRankPanel() {

}

void PreviewViewController::UpdateEnergyBar(float fillAmount) {

}

void PreviewViewController::UpdateProgressBar(float time) {

}

#include "UnityEngine/WaitUntil.hpp"
#include "System/Func_1.hpp"
#include "System/Collections/IEnumerator.hpp"
#include "custom-types/shared/delegate.hpp"

custom_types::Helpers::Coroutine PreviewViewController::FinalizePanels() {
    std::function<bool()> func = [this]() {
	  return objectGrabber->isCompleted;
	};

	co_yield reinterpret_cast<System::Collections::IEnumerator*>(WaitUntil::New_ctor(custom_types::MakeDelegate<System::Func_1<bool>*>(func)));

    auto multiplierPanel = objectGrabber->multiplierPanel;
    auto comboPanel = objectGrabber->comboPanel;
    auto progressPanel = objectGrabber->progressPanel;

    objectGrabber->multiplierPanel->SetActive(true);
    multiplierText = multiplierPanel->GetComponentsInChildren<CurvedTextMeshPro*>().Last();
    multiplierCircles = multiplierPanel->get_transform()->GetComponentsInChildren<Image*>();
    // TODO: MULTIPLIER CIRCLES
//    multiplierCircles[0].color = CONFIG_MULTIPLIER_ONE;
//    multiplierCircles[1].color = CONFIG_MULTIPLIER_ONE_WITH_ALPHA_0.25

    energyBar = objectGrabber->energyPanel->get_transform()->Find("EnergyBarWrapper/EnergyBar")->GetComponent<Image*>();

    comboLines = comboPanel->get_transform()->GetComponentsInChildren<ImageView*>();
    numText = comboPanel->get_transform()->Find("ComboCanvas/NumText")->GetComponent<CurvedTextMeshPro*>();
    comboText = comboPanel->get_transform()->Find("ComboText")->GetComponent<CurvedTextMeshPro*>();

    progressPanelImages = progressPanel->get_transform()->GetComponentsInChildren<Image*>();
    auto texts = progressPanel->get_transform()->GetComponentsInChildren<CurvedTextMeshPro*>();
    texts[2]->set_text("0");
    texts[3]->set_text("01");

    auto immediateRankTransform = objectGrabber->immediateRankPanel->get_transform();
    scoreText = immediateRankTransform->Find("ScoreText")->GetComponent<CurvedTextMeshPro*>();
    percentageText = immediateRankTransform->Find("RelativeScoreText")->GetComponent<CurvedTextMeshPro*>();
    rankText = immediateRankTransform->Find("ImmediateRankText")->GetComponent<CurvedTextMeshPro*>();

    immediateRankTransform->set_localPosition({0.75f, 0, 0});

    previewToggleIsReady = true;
    UpdatePanelVisibility(0);
    co_return;
}

#include "UnityEngine/WaitForSecondsRealtime.hpp"

custom_types::Helpers::Coroutine PreviewViewController::MultiplierPreviewCoroutine() {
  while(true) {
	std::function<bool()> func = [this]() {
	  return previewToggleIsReady;
	};

	co_yield reinterpret_cast<System::Collections::IEnumerator*>(WaitUntil::New_ctor(custom_types::MakeDelegate<System::Func_1<bool>*>(func)));
	previewCoroOn8x = false;
	multiplierCircles[0]->set_fillAmount(0.5f);

	//  multiplierCircles[0].color = Config.Multiplier.One.ColorWithAlpha(0.25f);
	//  multiplierCircles[1].color = Config.Multiplier.One;
	multiplierText->set_text("1");
	co_yield reinterpret_cast<System::Collections::IEnumerator*>(WaitForSecondsRealtime::New_ctor(1));

	//  multiplierCircles[0].color = Config.Multiplier.Two.ColorWithAlpha(0.25f);
	//  multiplierCircles[1].color = Config.Multiplier.Two;
	multiplierText->set_text("2");
	co_yield reinterpret_cast<System::Collections::IEnumerator*>(WaitForSecondsRealtime::New_ctor(1));

	//  multiplierCircles[0].color = Config.Multiplier.Four.ColorWithAlpha(0.25f);
	//  multiplierCircles[1].color = Config.Multiplier.Four;
	multiplierText->set_text("4");
	co_yield reinterpret_cast<System::Collections::IEnumerator*>(WaitForSecondsRealtime::New_ctor(1));

	previewCoroOn8x = true;
	multiplierText->set_text("8");
	multiplierCircles[1]->set_fillAmount(0);
	//  if (!Config.Multiplier.RainbowOnMaxMultiplier)
	//	multiplierCircles[0]->set_color(Config.Multiplier.Eight.ColorWithAlpha(0.25f);
	co_yield reinterpret_cast<System::Collections::IEnumerator*>(WaitForSecondsRealtime::New_ctor(1));
  }
}