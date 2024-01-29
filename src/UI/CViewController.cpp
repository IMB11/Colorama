#include "UI/CViewController.hpp"
#include "UI/CFlowCoordinator.hpp"

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "UnityEngine/Application.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"

#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

#include "UI/MenuColorViewController.hpp"
#include "UI/AtmosphereViewController.hpp"

#include "UnityEngine/Events/UnityEvent_1.hpp"
#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"

#include "Colorama.hpp"

#include <map>
#include <utility>

using namespace Colorama::UI;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace HMUI;

DEFINE_TYPE(Colorama::UI, CViewController);

void CViewController::DidActivate(bool firstActivation, bool addedToHierarchy,
                                  bool screenSystemEnabling) {
    using namespace GlobalNamespace;
    using namespace QuestUI;

    if (firstActivation) {
        VerticalLayoutGroup *verticalLayoutGroup =
            BeatSaberUI::CreateVerticalLayoutGroup(get_transform());

        const auto enabled_toggle = AddConfigValueToggle(
            verticalLayoutGroup->get_transform(), getColoramaConfig().Enabled);

        const std::function e = [&](bool value) {
            if (menuColorsButton) {
                menuColorsButton->set_interactable(
                    getColoramaConfig().Enabled.GetValue());
            }
            if (atmosphereButton) {
                atmosphereButton->set_interactable(
                    getColoramaConfig().Enabled.GetValue());
            }
        };

        enabled_toggle->onValueChanged->AddListener(
            custom_types::MakeDelegate<Events::UnityAction_1<bool> *>(e));

        GameObject *scrollView =
            BeatSaberUI::CreateScrollView(verticalLayoutGroup->get_transform());
        auto *scrollViewLayoutElement =
            scrollView->GetComponentInParent<LayoutElement *>();
        scrollViewLayoutElement->set_preferredWidth(120);
        scrollViewLayoutElement->set_preferredHeight(65);

        const auto mCvC = QuestUI::BeatSaberUI::CreateViewController<
            MenuColorViewController *>();
        mCvC->parentFlowCoordinator = flowCoordinator;
        menuColorsButton = CreateUIViewControllerButton(
            scrollView->get_transform(), "Lighting",
            "Change the lighting around the menus.", mCvC);

        menuColorsButton->set_interactable(
            getColoramaConfig().Enabled.GetValue());

        const auto avC = QuestUI::BeatSaberUI::CreateViewController<
            AtmosphereViewController *>();
        avC->parentFlowCoordinator = flowCoordinator;
        atmosphereButton = CreateUIViewControllerButton(
            scrollView->get_transform(), "Environment",
            "Change options related to objects in the menus.", avC);

        atmosphereButton->set_interactable(
            getColoramaConfig().Enabled.GetValue());

        HorizontalLayoutGroup *horizontalLayoutGroup =
            BeatSaberUI::CreateHorizontalLayoutGroup(
                verticalLayoutGroup->get_transform());
        horizontalLayoutGroup->set_padding(RectOffset::New_ctor(8, 0, -5, 5));

        BeatSaberUI::CreateText(horizontalLayoutGroup->get_transform(),
                                "Colorama (GPL-2.0) IMB11", Vector2::get_zero(),
                                Vector2(4, 4));
        Button *donateButton = BeatSaberUI::CreateUIButton(
            horizontalLayoutGroup->get_transform(), "Support Discord",
            [] { Application::OpenURL("https://discord.imb11.dev/"); });
        BeatSaberUI::SetButtonTextSize(donateButton, 3);
    }
}

Button *CViewController::CreateUIViewControllerButton(
    Transform *parent, const std::string& title, std::string description,
    ViewController *viewController) const {
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
        BeatSaberUI::CreateVerticalLayoutGroup(
            horizontalLayoutGroup->get_transform());
    verticalLayoutGroup->set_spacing(-5);
    verticalLayoutGroup->set_padding(RectOffset::New_ctor(0, 0, 2, 0));
    auto *verticalLayoutGroupLayoutElement =
        verticalLayoutGroup->GetComponent<LayoutElement *>();
    verticalLayoutGroupLayoutElement->set_preferredWidth(65);

    BeatSaberUI::CreateText(verticalLayoutGroup->get_transform(), title,
                            Vector2::get_zero())
        ->set_fontSize(5);
    BeatSaberUI::CreateText(verticalLayoutGroup->get_transform(), std::move(description),
                            Vector2::get_zero())
        ->set_fontSize(3);

    Button *openButton = BeatSaberUI::CreateUIButton(
        horizontalLayoutGroup->get_transform(), ">", "PlayButton",
        [this, title, viewController]() {
            flowCoordinator->SetTitle(title, AnimationType::In);
            flowCoordinator->ReplaceTopViewController(
                viewController, flowCoordinator, flowCoordinator, nullptr,
                AnimationType::In,
                AnimationDirection::Horizontal);

            reinterpret_cast<CFlowCoordinator *>(flowCoordinator)
                ->currentViewController = viewController;
        });
    BeatSaberUI::SetButtonTextSize(openButton, 5);

    Destroy(openButton->get_transform()
                        ->Find("Content")
                        ->GetComponent<LayoutElement *>());

    auto *contentSizeFitter =
        openButton->get_gameObject()->AddComponent<ContentSizeFitter *>();
    contentSizeFitter->set_horizontalFit(
        ContentSizeFitter::FitMode::PreferredSize);
    contentSizeFitter->set_verticalFit(
        ContentSizeFitter::FitMode::PreferredSize);

    return openButton;
}