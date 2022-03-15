#include "UI/MainViewController.hpp"
#include "HMUI/Touchable.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "HMUI/Screen.hpp"

using namespace Colorama::UI;
using namespace QuestUI;

void MainViewController::DidActivate(HMUI::ViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    getLogger().info("DidActivate: %p, %d, %d, %d", self, firstActivation,
                     addedToHierarchy, screenSystemEnabling);

    if(firstActivation) {
        self->get_gameObject()->AddComponent<HMUI::Touchable*>();
        GameObject* container = BeatSaberUI::CreateScrollableSettingsContainer(self->get_transform());


        auto menuTitle = BeatSaberUI::CreateText(container->get_transform(), "Menu Colors");
        menuTitle->set_fontSize(16);
        BeatSaberUI::CreateText(container->get_transform(), " \nColors will apply after you close this page.");
        BeatSaberUI::CreateText(container->get_transform(), "");

        AddConfigValueToggle(container->get_transform(), getColoramaConfig().Menu_Enabled);
        AddConfigValueColorPicker(container->get_transform(), getColoramaConfig().Menu_GamemodeColor);
        AddConfigValueColorPicker(container->get_transform(), getColoramaConfig().Menu_FreeplayColor);
        AddConfigValueColorPicker(container->get_transform(), getColoramaConfig().Menu_ResultsColor);
        AddConfigValueColorPicker(container->get_transform(), getColoramaConfig().Menu_ResultsFailColor);

        AddConfigValueColorPicker(container->get_transform(), getColoramaConfig().Menu_CampaignsColor);
        AddConfigValueColorPicker(container->get_transform(), getColoramaConfig().Menu_FeetColor);
    }
}