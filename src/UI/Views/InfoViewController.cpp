#include "UI/Views/InfoViewController.hpp"

DEFINE_TYPE(Colorama::UI, InfoViewController)

using namespace Colorama::UI;

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "UnityEngine/Application.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

UnityEngine::UI::Button *CreateApplicationButton(
    UnityEngine::Transform *parent, std::string title, std::string description, std::string URL) {
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

  BeatSaberUI::CreateText(verticalLayoutGroup->get_transform(), title,
                          Vector2::get_zero())
      ->set_fontSize(5);
  BeatSaberUI::CreateText(verticalLayoutGroup->get_transform(), description,
                          Vector2::get_zero())
      ->set_fontSize(3);

  Button *openButton = QuestUI::BeatSaberUI::CreateUIButton(
      horizontalLayoutGroup->get_transform(), ">", "PlayButton",
      [URL]() {
        Application::OpenURL(URL);
  });
  BeatSaberUI::SetButtonTextSize(openButton, 5);

  Object::Destroy(openButton->get_transform()
                      ->Find("Content")
                      ->GetComponent<LayoutElement *>());

  ContentSizeFitter *contentSizeFitter =
      openButton->get_gameObject()->AddComponent<ContentSizeFitter *>();
  contentSizeFitter->set_horizontalFit(
      ContentSizeFitter::FitMode::PreferredSize);
  contentSizeFitter->set_verticalFit(
      ContentSizeFitter::FitMode::PreferredSize);

  return openButton;
}

void InfoViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
  using namespace HMUI;
  using namespace UnityEngine;
  using namespace UnityEngine::UI;
  using namespace QuestUI;

  if(firstActivation) {
    auto vertGroup = BeatSaberUI::CreateVerticalLayoutGroup(get_transform());
    auto titleText = BeatSaberUI::CreateText(vertGroup->get_transform(), "<size=18><b>Colorama</b></size> v3.0.0");

  }
}