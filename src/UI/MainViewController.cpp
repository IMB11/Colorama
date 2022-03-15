#include "UI/MainViewController.hpp"
#include "HMUI/Touchable.hpp"

using namespace Colorama::UI;
using namespace QuestUI;

void MainViewController::DidActivate(HMUI::ViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    getLogger().info("DidActivate: %p, %d, %d, %d", self, firstActivation,
                     addedToHierarchy, screenSystemEnabling);

    if(firstActivation) {
        self->get_gameObject()->AddComponent<HMUI::Touchable*>();
        GameObject* container = BeatSaberUI::CreateScrollableSettingsContainer(self->get_transform());

        BeatSaberUI::CreateText(container->get_transform(), "Gameplay Colors")->set_fontSize(12);
        BeatSaberUI::CreateText(container->get_transform(), "These options change various colors during gameplay - such as arrow colors. Noodle/Chroma may override these.");

        AddConfigValueToggle(container->get_transform(), getColoramaConfig().Game_Enabled);

        AddConfigValueToggle(container->get_transform(), getColoramaConfig().Game_LEnabled);
        AddConfigValueColorPicker(container->get_transform(), getColoramaConfig().Game_LColor);

        AddConfigValueToggle(container->get_transform(), getColoramaConfig().Game_REnabled);
        AddConfigValueColorPicker(container->get_transform(), getColoramaConfig().Game_RColor);
    }
}