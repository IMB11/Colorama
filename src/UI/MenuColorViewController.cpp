#include "UI/MenuColorViewController.hpp"

#include "System/Action_2.hpp"

#include "GlobalNamespace/ColorChangeUIEventType.hpp"
#include "GlobalNamespace/ColorSO.hpp"
#include "GlobalNamespace/MenuLightsPresetSO.hpp"
#include "GlobalNamespace/MenuLightsPresetSO_LightIdColorPair.hpp"
#include "GlobalNamespace/SimpleColorSO.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/ScriptableObject.hpp"

DEFINE_TYPE(Colorama::UI, MenuColorViewController);

using namespace HMUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace QuestUI;
using namespace GlobalNamespace;
using namespace Colorama::UI;

namespace MCV_Utils {
    GlobalNamespace::ColorSO *createColorSO(Color color) {
        float t = color.r + color.g + color.b;
        auto so = ScriptableObject::CreateInstance<
            GlobalNamespace::SimpleColorSO *>();
        so->dyn__color() = color;
        return so;
    }

    GlobalNamespace::MenuLightsPresetSO *createMenuLights(Color color) {
        float t = color.r + color.g + color.b;
        auto colorSO = createColorSO(color);
        auto menuPresetSO = Object::Instantiate(defaultLights);
        auto colorPairs = menuPresetSO->dyn__lightIdColorPairs();
        for (int i = 0; i < colorPairs.Length(); ++i) {
            auto pair = GlobalNamespace::MenuLightsPresetSO::LightIdColorPair::
                New_ctor();
            pair->dyn_lightId() = colorPairs[i]->dyn_lightId();
            pair->dyn_baseColor() = colorSO;
            pair->dyn_intensity() = colorPairs[i]->dyn_intensity();
            colorPairs[i] = pair;
        }
        return menuPresetSO;
    }
} // namespace MCV_Utils

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
