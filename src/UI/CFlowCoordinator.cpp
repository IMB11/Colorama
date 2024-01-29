#include "UI/CFlowCoordinator.hpp"
#include "HMUI/ViewController.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"

using namespace Colorama::UI;

DEFINE_TYPE(Colorama::UI, CFlowCoordinator);

void CFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    using namespace GlobalNamespace;
    using namespace HMUI;
    using namespace UnityEngine;

    if (firstActivation) {
        SetTitle("Colorama", ViewController::AnimationType::Out);
        showBackButton = true;
        cViewController = QuestUI::BeatSaberUI::CreateViewController<CViewController*>();
        cViewController->flowCoordinator = this;

        currentViewController = nullptr;

        ProvideInitialViewControllers(cViewController, nullptr, nullptr, nullptr, nullptr);
    }
}

void CFlowCoordinator::BackButtonWasPressed(
    HMUI::ViewController* topViewController
) {
    using namespace GlobalNamespace;
    using namespace HMUI;
    using namespace UnityEngine;

    if (currentViewController) {
        SetTitle(MOD_ID, ViewController::AnimationType::In);
        ReplaceTopViewController(cViewController, this, this, nullptr, ViewController::AnimationType::Out, ViewController::AnimationDirection::Horizontal);

        currentViewController = nullptr;
    } else {
        parentFlowCoordinator->DismissFlowCoordinator(this, ViewController::AnimationDirection::Horizontal, nullptr, false);
    }
}