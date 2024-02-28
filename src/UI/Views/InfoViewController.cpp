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
                                                 const std::string &URL) {
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

  BeatSaberUI::CreateText(verticalLayoutGroup->get_transform(),
                          std::move(title), Vector2::get_zero())
      ->set_fontSize(5);
  BeatSaberUI::CreateText(verticalLayoutGroup->get_transform(),
                          std::move(description), Vector2::get_zero())
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
#include "UI/ColoramaFlowCoordinator.hpp"

void InfoViewController::ShowDonationModal() {
  using namespace QuestUI;

  ColoramaFlowCoordinator* flow_coordinator = reinterpret_cast<ColoramaFlowCoordinator*>(this->parentFlow);
  HMUI::ModalView* modalView = BeatSaberUI::CreateModal(flow_coordinator->_configViewController->get_transform(), UnityEngine::Vector2(80.0f, 88.0f), [](HMUI::ModalView* modalView){
        Destroy(modalView->get_gameObject());
    });

  auto layout = BeatSaberUI::CreateVerticalLayoutGroup(modalView->get_transform());
  layout->GetComponent<UnityEngine::UI::ContentSizeFitter*>()->set_horizontalFit(UnityEngine::UI::ContentSizeFitter::FitMode::Unconstrained);

  layout->set_padding(UnityEngine::RectOffset::New_ctor(2, 2, 4, 4));
  layout->set_childAlignment(UnityEngine::TextAnchor::UpperLeft);
  layout->set_childControlHeight(true);
  layout->set_childForceExpandHeight(false);
  layout->set_childControlWidth(false);
  layout->set_childForceExpandWidth(true);

  auto hoz1 = BeatSaberUI::CreateHorizontalLayoutGroup(layout);
  hoz1->GetComponent<UnityEngine::UI::LayoutElement*>()->set_ignoreLayout(true);
  auto rectHoz1 = hoz1->get_rectTransform();
  rectHoz1->set_anchorMax({0.97f, 1.0f});
  rectHoz1->set_anchorMin({0.03f, 1.0f});
  rectHoz1->set_anchoredPosition({0.0f, -5.0f});

  auto hozText = BeatSaberUI::CreateText(hoz1, "Support Me On Ko-Fi!");
  hozText->set_alignment(TMPro::TextAlignmentOptions::Center);

  auto text2 = BeatSaberUI::CreateText(layout, "Enjoying Colorama? Support it's development on Ko-Fi!");
  text2->set_enableWordWrapping(true);
  text2->set_alignment(TMPro::TextAlignmentOptions::Center);

  auto hoz2 = BeatSaberUI::CreateHorizontalLayoutGroup(layout);
  BeatSaberUI::CreateUIButton(hoz2, "Open Ko-Fi", [] {
    Application::OpenURL("https://ko-fi.com/mineblock11");
  });

  INFO("Showing modal!")
  modalView->Show(true, false, nullptr);
}


void InfoViewController::DidActivate(bool firstActivation,
                                     bool addedToHierarchy,
                                     bool screenSystemEnabling) {
  using namespace HMUI;
  using namespace UnityEngine;
  using namespace UnityEngine::UI;
  using namespace QuestUI;

  static const std::string version = "3.0.1";

  if (firstActivation) {
    // INFO("{}", getColoramaConfig().donationShownVersion.GetValue())
    //   if(getColoramaConfig().donationShownVersion.GetValue() != version) {
    //     // getColoramaConfig().donationShownVersion.SetValue(version);
    //     // ShowDonationModal();
    //   }

	auto vertGroup = BeatSaberUI::CreateVerticalLayoutGroup(get_transform());
	auto titleText = BeatSaberUI::CreateText(
	    vertGroup->get_transform(), string_format("<size=18><b>Colorama</b></size> v%s", version.c_str()));

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
	                        " https://discord.imb11.dev/");
	CreateApplicationButton(scrollView->get_transform(), "GitHub",
	                        "Checkout the GitHub repository for Colorama.",
	                        " https://github.com/IMB11/Colorama");
    CreateApplicationButton(scrollView->get_transform(), "Support",
                            "Support Colorama's development on Ko-Fi!",
                            " https://ko-fi.com/mineblock11");

	HorizontalLayoutGroup *horizontalLayoutGroup =
	    QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(
	        vertGroup->get_transform());

	auto year = getCurrentYear();

	auto licenseText = BeatSaberUI::CreateText(
	    horizontalLayoutGroup->get_transform(),
	    string_format("Colorama %d (GPL-2.0) IMB11 (mineblock11)", year),
	    Vector2::get_zero(), Vector2(4, 4));

	licenseText->set_alignment(TMPro::TextAlignmentOptions::_get_Center());
  }
}