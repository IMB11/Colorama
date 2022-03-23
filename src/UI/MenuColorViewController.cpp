#include "UI/MenuColorViewController.hpp"

#include "System/Action_2.hpp"

#include "GlobalNamespace/ColorChangeUIEventType.hpp"

DEFINE_TYPE(Colorama::UI, MenuColorViewController);

using namespace HMUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace QuestUI;
using namespace GlobalNamespace;
using namespace Colorama::UI;

void MenuColorViewController::DidActivate(bool firstActivation,
                                          bool addedToHierarchy,
                                          bool screenSystemEnabling) {
    if (firstActivation) {
        GameObject *container =
            BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        AddConfigValueColorPicker(
            container->get_transform(), getColoramaConfig().Menu_GamemodeColor);
        AddConfigValueColorPicker(
            container->get_transform(), getColoramaConfig().Menu_FreeplayColor);
        AddConfigValueColorPicker(
            container->get_transform(), getColoramaConfig().Menu_ResultsColor);
        AddConfigValueColorPicker(
            container->get_transform(),
            getColoramaConfig().Menu_ResultsFailColor);
        AddConfigValueColorPicker(
            container->get_transform(),
            getColoramaConfig().Menu_CampaignsColor);
    }
}
