#include "UI/MenuColorViewController.hpp"

#include "System/Action_2.hpp"

#include "GlobalNamespace/ColorChangeUIEventType.hpp"

#include "UI/CViewController.hpp"
#include "UI/CFlowCoordinator.hpp"

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

DEFINE_TYPE(Colorama::UI, MenuColorViewController);

#define reset_clr(a) getColoramaConfig().a.SetValue(UnityEngine::Color::get_cyan());

using namespace HMUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace QuestUI;
using namespace GlobalNamespace;
using namespace Colorama::UI;

template<::QuestUI::BeatSaberUI::HasTransform P>
inline ::QuestUI::ColorSetting* CreateConfigValueColorPicker(P parent, ConfigUtils::ConfigValue<ConfigUtils::Color>& configValue) {
    auto object = ::QuestUI::BeatSaberUI::CreateColorPicker(parent, configValue.GetName(), configValue.GetValue(),
                                                            [&configValue](::UnityEngine::Color value) {
                                                                configValue.SetValue(value);
                                                            }
    );
    if(!configValue.GetHoverHint().empty())
        ::QuestUI::BeatSaberUI::AddHoverHint(object, configValue.GetHoverHint());
    return object;
}

void MenuColorViewController::DidActivate(bool firstActivation,
                                          bool addedToHierarchy,
                                          bool screenSystemEnabling) {
    if (firstActivation) {
        GameObject *container =
            BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        BeatSaberUI::CreateUIButton(container->get_transform(), "Reset All", [this]() {
            reset_clr(Menu_GamemodeColor);
            reset_clr(Menu_FreeplayColor);
            reset_clr(Menu_ResultsColor);
            reset_clr(Menu_ResultsFailColor);
            reset_clr(Menu_CampaignsColor);

            parentFlowCoordinator->DismissViewController(this, ViewController::AnimationDirection::Horizontal, nullptr, false);
        });

        CreateConfigValueColorPicker(
            container->get_transform(), getColoramaConfig().Menu_GamemodeColor);
        CreateConfigValueColorPicker(
            container->get_transform(), getColoramaConfig().Menu_FreeplayColor);
        CreateConfigValueColorPicker(
            container->get_transform(), getColoramaConfig().Menu_ResultsColor);
        CreateConfigValueColorPicker(
            container->get_transform(),
            getColoramaConfig().Menu_ResultsFailColor);
        CreateConfigValueColorPicker(
            container->get_transform(),
            getColoramaConfig().Menu_CampaignsColor);
    }
}
