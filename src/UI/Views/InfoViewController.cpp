#include "UI/Views/InfoViewController.hpp"

DEFINE_TYPE(Colorama::UI, InfoViewController)

using namespace Colorama::UI;

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "UnityEngine/Application.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

UnityEngine::UI::Button *CreateApplicationButton(UnityEngine::Transform *parent,
                                                 std::string title,
                                                 std::string description,
                                                 const std::string& URL) {
  using namespace HMUI;
  using namespace UnityEngine;
  using namespace UnityEngine::UI;
  using namespace QuestUI;

  HorizontalLayoutGroup *horizontalLayoutGroup =
      BeatSaberUI::CreateHorizontalLayoutGroup(parent);
  auto *horizontalLayoutGroupBackgroundable =
      horizontalLayoutGroup->GetComponent<Backgroundable *>();
  horizontalLayoutGroupBackgroundable->ApplyBackground("panel-top");
  horizontalLayoutGroupBackgroundable->GetComponentInChildren<ImageView *>()
      ->skew = .18f;
  auto *horizontalLayoutGroupLayoutElement =
      horizontalLayoutGroup->GetComponent<LayoutElement *>();
  horizontalLayoutGroupLayoutElement->set_preferredWidth(100);
  horizontalLayoutGroupLayoutElement->set_preferredHeight(15);

  VerticalLayoutGroup *verticalLayoutGroup =
      QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(
          horizontalLayoutGroup->get_transform());
  verticalLayoutGroup->set_spacing(-5);
  verticalLayoutGroup->set_padding(RectOffset::New_ctor(0, 0, 2, 0));
  auto *verticalLayoutGroupLayoutElement =
      verticalLayoutGroup->GetComponent<LayoutElement *>();
  verticalLayoutGroupLayoutElement->set_preferredWidth(65);

  BeatSaberUI::CreateText(verticalLayoutGroup->get_transform(), std::move(title),
                          Vector2::get_zero())
      ->set_fontSize(5);
  BeatSaberUI::CreateText(verticalLayoutGroup->get_transform(), std::move(description),
                          Vector2::get_zero())
      ->set_fontSize(3);

  Button *openButton = QuestUI::BeatSaberUI::CreateUIButton(
      horizontalLayoutGroup->get_transform(), ">", "PlayButton",
      [URL]() { Application::OpenURL(URL); });
  BeatSaberUI::SetButtonTextSize(openButton, 5);

  Object::Destroy(openButton->get_transform()
                      ->Find("Content")
                      ->GetComponent<LayoutElement *>());

  auto *contentSizeFitter =
      openButton->get_gameObject()->AddComponent<ContentSizeFitter *>();
  contentSizeFitter->set_horizontalFit(
      ContentSizeFitter::FitMode::PreferredSize);
  contentSizeFitter->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);

  return openButton;
}

#include <chrono>
#include <utility>

int getCurrentYear() {
  using namespace std::chrono;
  return static_cast<int>(
      year_month_day {time_point_cast<days>(system_clock::now())}.year());
}

#include "System/Collections/ArrayList.hpp"
#include "UI/Components/Shimmer.hpp"
#include "UnityEngine/GradientAlphaKey.hpp"
#include "UnityEngine/GradientColorKey.hpp"

// Gradient* populateRainbowGradient(UnityEngine::Gradient* gradient) {
//   using namespace UnityEngine;
//   using namespace UnityEngine::UI;
//   using namespace System::Collections;
//
//   std::vector<GradientColorKey> colorKeys = {};
//   std::vector<GradientAlphaKey> alphaKeys = {};
//
//   for(float i = 0.0f; i < 1.0f; i+=0.01f)
//   {
//	Color c = Color::HSVToRGB(i, 0.5f, 0.5f);
//	LOG("%s", static_cast<std::string>(c.ToString()).c_str());
//	auto colorKey = GradientColorKey(c, i);
//	auto alphaKey = GradientAlphaKey(1.0f, i);
//	colorKeys.emplace_back(colorKey);
//	alphaKeys.emplace_back(alphaKey);
//   }
//   LOG("Is it this!?");
//   gradient->SetKeys(il2cpp_utils::vectorToArray(colorKeys),
//   il2cpp_utils::vectorToArray(alphaKeys)); LOG("NAH"); return gradient;
// }

void InfoViewController::DidActivate(bool firstActivation,
                                     bool addedToHierarchy,
                                     bool screenSystemEnabling) {
  using namespace HMUI;
  using namespace UnityEngine;
  using namespace UnityEngine::UI;
  using namespace QuestUI;

  if (firstActivation) {
	auto vertGroup = BeatSaberUI::CreateVerticalLayoutGroup(get_transform());
	auto titleText = BeatSaberUI::CreateText(
	    vertGroup->get_transform(), "<size=18><b>Colorama</b></size> v3.0.0");

	titleText->set_alignment(TMPro::TextAlignmentOptions::_get_Center());
	titleText->get_gameObject()->AddComponent<Components::Shimmer *>();

	GameObject *scrollView =
	    QuestUI::BeatSaberUI::CreateScrollView(vertGroup->get_transform());
	auto *scrollViewLayoutElement =
	    scrollView->GetComponentInParent<LayoutElement *>();
	scrollViewLayoutElement->set_preferredWidth(120);
	scrollViewLayoutElement->set_preferredHeight(65);

	CreateApplicationButton(scrollView->get_transform(), "Discord",
	                        "Join my discord to stay updated with the latest "
	                        "releases and come chat!",
	                        " https://discord.gg/UzHtJKqHny");
	CreateApplicationButton(scrollView->get_transform(), "Website",
	                        "Checkout my blog and social links on my website.",
	                        " https://mineblock11.dev/");

	HorizontalLayoutGroup *horizontalLayoutGroup =
	    QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(
	        vertGroup->get_transform());

	auto year = getCurrentYear();

	auto licenseText = BeatSaberUI::CreateText(
	    horizontalLayoutGroup->get_transform(),
	    string_format("Colorama %d (GPL-2.0) mineblock11", year),
	    Vector2::get_zero(), Vector2(4, 4));

	licenseText->set_alignment(TMPro::TextAlignmentOptions::_get_Center());
  }
}