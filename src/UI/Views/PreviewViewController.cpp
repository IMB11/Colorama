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

    if(firstActivation && grabber == nullptr) {
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
  return min + rand() % (max + 1 - min);
}

void PreviewViewController::UpdatePanelVisibility(int idx) {
    if(objectGrabber == nullptr) return;
	if(!objectGrabber->isCompleted) return;

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
	    objectGrabber->multiplierPanel->get_transform()->set_localPosition(VOID_VECT3);
	    objectGrabber->energyPanel->SetActive(false);
	    objectGrabber->comboPanel->SetActive(false);
	    objectGrabber->progressPanel->SetActive(false);
	    objectGrabber->immediateRankPanel->SetActive(false);
	    break;
	  case 1:
	    objectGrabber->multiplierPanel->get_transform()->set_localPosition(VOID_VECT3);
	    objectGrabber->energyPanel->SetActive(true);
	    objectGrabber->comboPanel->SetActive(false);
	    objectGrabber->progressPanel->SetActive(false);
	    objectGrabber->immediateRankPanel->SetActive(false);
	    break;
	  case 2:
	    objectGrabber->multiplierPanel->get_transform()->set_localPosition(Vector3::get_zero());
	    objectGrabber->energyPanel->SetActive(false);
	    objectGrabber->comboPanel->SetActive(false);
	    objectGrabber->progressPanel->SetActive(false);
	    objectGrabber->immediateRankPanel->SetActive(false);
	    break;
	  case 3:
	    objectGrabber->multiplierPanel->get_transform()->set_localPosition(VOID_VECT3);
	    objectGrabber->energyPanel->SetActive(false);
	    objectGrabber->comboPanel->SetActive(false);
	    objectGrabber->progressPanel->SetActive(true);
	    objectGrabber->immediateRankPanel->SetActive(false);
	    break;
	  case 4:
	    objectGrabber->multiplierPanel->get_transform()->set_localPosition(VOID_VECT3);
	    objectGrabber->energyPanel->SetActive(false);
	    objectGrabber->comboPanel->SetActive(true);
	    objectGrabber->progressPanel->SetActive(false);
	    objectGrabber->immediateRankPanel->SetActive(false);

	    numText->set_text(std::to_string(random(0, 250)));
	    objectGrabber->comboPanel->get_transform()->set_localPosition(Vector3::get_zero());
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
	    UpdateEnergyBar();
	    // TODO: Rainbow On Max Config
	    break;
	  case 2:
	    // TODO: Multiplier Rainbow On Max Config
		break;
	  case 3:
	    UpdateProgressBar();
	    break;
	  case 4:
	    UpdateComboPanel();
//	    UpdateImmediateRankPanel();
    }
}

void PreviewViewController::UpdateComboPanel() {
  ComboConfiguration config = getColoramaConfig().comboConfiguration.GetValue();
  objectGrabber->comboPanel->SetActive(false);
  objectGrabber->comboPanel->SetActive(true);
  if(config.useGradient) {

    comboLines[0]->gradient = true;
    comboLines[0]->set_color(Color::get_white());
    comboLines[1]->gradient = true;
    comboLines[1]->set_color(Color::get_white());

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

namespace PreviewUtils {
float repeat(float t, float length = 1.0F) {
  return std::clamp(t - std::floor(t / length) * length, 0.0f, length);
}

float pingPong(float t, float length = 1.0F) {
  t = repeat(t, length * 2.0F);
  return length - std::abs(t - length);
}
}


void PreviewViewController::UpdateImmediateRankPanel() {

}

void PreviewViewController::UpdateEnergyBar() {
  EnergyBarConfiguration config = getColoramaConfig().energyBarConfiguration.GetValue();

  energyBar->get_rectTransform()->set_anchorMax(Vector2(fillAmount, 1.0F));

  energyBar->get_gameObject()->set_active(false);
  energyBar->get_gameObject()->set_active(true);

  if (fillAmount == 1.0F && config.rainbowFull) {
    energyBar->set_color(Color::HSVToRGB(PreviewUtils::pingPong(Time::get_time() * 0.5F, 1.0F), 1.0F, 1.0F));
    return;
  }

  if (fillAmount == 1.0F) {
    energyBar->set_color(config.highColor);
  }

  if (fillAmount == 0.5F) {
    energyBar->set_color(config.midColor);
  }

  if (fillAmount > 0.5F && fillAmount < 1) {
    energyBar->set_color(Color::Lerp(config.midColor, config.highColor, (fillAmount - 0.5F) * 2));
  }

  if(fillAmount < 0.5F) {
    energyBar->set_color(Color::Lerp(config.lowColor, config.midColor, fillAmount * 2));
  }
}

void PreviewViewController::UpdateProgressBar() {
  ProgressBarConfiguration config = getColoramaConfig().progressBarConfiguration.GetValue();

  Color colorWithAlpha = Color(config.bgColor.r, config.bgColor.g, config.bgColor.b, 0.25F);
  progressPanelImages[1]->set_color(colorWithAlpha);
  progressPanelImages[2]->set_color(config.handleColor);

  float modifiedFill = (progressFillAmount - 0.5F) * 50;
  progressPanelImages[2]->get_transform()->set_localPosition(Vector3(modifiedFill, 0, 0));
  progressPanelImages[0]->get_rectTransform()->set_anchorMax(Vector2(progressFillAmount, 1));

  if(config.enableGradient) {
    progressPanelImages[0]->set_color(Color::Lerp(config.startColor, config.endColor, progressFillAmount));
  } else {
    progressPanelImages[0]->set_color(config.fillColor);
  }
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
    // multiplierCircles[0].color = CONFIG_MULTIPLIER_ONE;
    // multiplierCircles[1].color = CONFIG_MULTIPLIER_ONE_WITH_ALPHA_0.25

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