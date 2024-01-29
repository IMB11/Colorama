#include "UI/AtmosphereViewController.hpp"

DEFINE_TYPE(Colorama::UI, AtmosphereViewController);

using namespace HMUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace QuestUI;
using namespace GlobalNamespace;
using namespace Colorama::UI;

void AtmosphereViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (firstActivation) {
        GameObject *container = BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
        const auto parent = container->get_transform();

        AddConfigValueToggle(parent, getColoramaConfig().Menu_LogoGlowLines);
        AddConfigValueToggle(parent, getColoramaConfig().Menu_Notes);
        AddConfigValueToggle(parent, getColoramaConfig().Menu_MenuFogRing);
        AddConfigValueToggle(parent, getColoramaConfig().Menu_MenuGround);
    }
}