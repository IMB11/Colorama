#include "Colorama.hpp"

#include "GlobalNamespace/BloomPrePassBackgroundColor.hpp"
#include "GlobalNamespace/CampaignFlowCoordinator.hpp"
#include "GlobalNamespace/MultiplayerModeSelectionFlowCoordinator.hpp"
#include "GlobalNamespace/PartyFreePlayFlowCoordinator.hpp"
#include "GlobalNamespace/SoloFreePlayFlowCoordinator.hpp"

#include <map>

using namespace GlobalNamespace;
using namespace Colorama;

namespace MFCH_Utils {
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
} // namespace MFCH_Utils

MAKE_HOOK_MATCH(MainMenu, &GlobalNamespace::MainFlowCoordinator::DidActivate,
                void, GlobalNamespace::MainFlowCoordinator *self, bool a,
                bool b, bool c) {
    using namespace MFCH_Utils;

    if (!defaultLights) {
        defaultLights = self->dyn__menuLightsManager()->dyn__defaultPreset();
    }

    mfc = self->dyn__menuLightsManager();

    auto soloFreeplay = self->dyn__soloFreePlayFlowCoordinator();
    auto partyFreeplay = self->dyn__partyFreePlayFlowCoordinator();
    auto campaignCoordinator = self->dyn__campaignFlowCoordinator();

    getLogger().info("MainFlowCoordinator::DidActivate - Begin Inject");

    if (getColoramaConfig().Enabled.GetValue()) {
        GameObject::Find("PlayersPlace")
            ->GetComponentInChildren<SpriteRenderer *>()
            ->set_color(getColoramaConfig().Menu_FeetColor.GetValue());

        GameObject *menuEnvCore = GameObject::Find("DefaultMenuEnvironment");

        if (menuEnvCore) {

            auto bgTransform =
                menuEnvCore->get_transform()->FindChild("GlowLines");
            if (bgTransform) {

                bgTransform->get_gameObject()->SetActive(
                    getColoramaConfig().Menu_LogoGlowLines.GetValue());
            }

            bgTransform =
                menuEnvCore->get_transform()->FindChild("GlowLines (1)");
            if (bgTransform) {

                bgTransform->get_gameObject()->SetActive(
                    getColoramaConfig().Menu_LogoGlowLines.GetValue());
            }

            bgTransform =
                menuEnvCore->get_transform()->FindChild("PileOfNotes");
            if (bgTransform) {

                bgTransform->get_gameObject()->SetActive(
                    getColoramaConfig().Menu_Notes.GetValue());
            }

            bgTransform = menuEnvCore->get_transform()->FindChild("Notes");
            if (bgTransform) {

                bgTransform->get_gameObject()->SetActive(
                    getColoramaConfig().Menu_Notes.GetValue());
            }

            bgTransform =
                menuEnvCore->get_transform()->FindChild("MenuFogRing");
            if (bgTransform) {

                bgTransform->get_gameObject()->SetActive(
                    getColoramaConfig().Menu_MenuFogRing.GetValue());
            }

            bgTransform =
                menuEnvCore->get_transform()->FindChild("BasicMenuGround");
            if (bgTransform) {

                bgTransform->get_gameObject()->SetActive(
                    getColoramaConfig().Menu_MenuGround.GetValue());
            }
        }

        self->dyn__defaultLightsPreset() =
            createMenuLights(getColoramaConfig().Menu_GamemodeColor.GetValue());
        soloFreeplay->dyn__defaultLightsPreset() =
            createMenuLights(getColoramaConfig().Menu_FreeplayColor.GetValue());
        partyFreeplay->dyn__defaultLightsPreset() =
            createMenuLights(getColoramaConfig().Menu_FreeplayColor.GetValue());
        soloFreeplay->dyn__resultsClearedLightsPreset() =
            createMenuLights(getColoramaConfig().Menu_ResultsColor.GetValue());
        partyFreeplay->dyn__resultsClearedLightsPreset() =
            createMenuLights(getColoramaConfig().Menu_ResultsColor.GetValue());
        campaignCoordinator->dyn__resultsClearedLightsPreset() =
            createMenuLights(getColoramaConfig().Menu_ResultsColor.GetValue());
        campaignCoordinator->dyn__resultsFailedLightsPreset() =
            createMenuLights(
                getColoramaConfig().Menu_ResultsFailColor.GetValue());
        soloFreeplay->dyn__resultsFailedLightsPreset() = createMenuLights(
            getColoramaConfig().Menu_ResultsFailColor.GetValue());
        partyFreeplay->dyn__resultsFailedLightsPreset() = createMenuLights(
            getColoramaConfig().Menu_ResultsFailColor.GetValue());
        campaignCoordinator->dyn__defaultLightsPreset() = createMenuLights(
            getColoramaConfig().Menu_CampaignsColor.GetValue());

    } else {

        GameObject *menuEnvCore = GameObject::Find("DefaultMenuEnvironment");

        if (menuEnvCore) {

            auto bgTransform =
                menuEnvCore->get_transform()->FindChild("GlowLines");
            if (bgTransform) { bgTransform->get_gameObject()->SetActive(true); }

            bgTransform =
                menuEnvCore->get_transform()->FindChild("GlowLines (1)");
            if (bgTransform) { bgTransform->get_gameObject()->SetActive(true); }

            bgTransform =
                menuEnvCore->get_transform()->FindChild("PlayersPlace");
            if (bgTransform) {

                bgTransform->get_gameObject()
                    ->GetComponentInChildren<SpriteRenderer *>()
                    ->set_color(Color::get_white());
            }

            bgTransform =
                menuEnvCore->get_transform()->FindChild("PileOfNotes");
            if (bgTransform) { bgTransform->get_gameObject()->SetActive(true); }

            bgTransform = menuEnvCore->get_transform()->FindChild("Notes");
            if (bgTransform) { bgTransform->get_gameObject()->SetActive(true); }

            bgTransform =
                menuEnvCore->get_transform()->FindChild("MenuFogRing");
            if (bgTransform) { bgTransform->get_gameObject()->SetActive(true); }

            bgTransform =
                menuEnvCore->get_transform()->FindChild("BasicMenuGround");
            if (bgTransform) { bgTransform->get_gameObject()->SetActive(true); }
        }

        self->dyn__defaultLightsPreset() = defaultLights;

        soloFreeplay->dyn__defaultLightsPreset() = defaultLights;

        partyFreeplay->dyn__defaultLightsPreset() = defaultLights;

        soloFreeplay->dyn__resultsClearedLightsPreset() = defaultLights;

        partyFreeplay->dyn__resultsClearedLightsPreset() = defaultLights;

        campaignCoordinator->dyn__resultsClearedLightsPreset() = defaultLights;

        campaignCoordinator->dyn__resultsFailedLightsPreset() =
            createMenuLights(Color::get_red());

        soloFreeplay->dyn__resultsFailedLightsPreset() =
            createMenuLights(Color::get_red());

        partyFreeplay->dyn__resultsFailedLightsPreset() =
            createMenuLights(Color::get_red());

        campaignCoordinator->dyn__defaultLightsPreset() = defaultLights;
    }

    getLogger().info("MainFlowCoordinator::DidActivate - End Inject");
    MainMenu(self, a, b, c);
}

void MainFlowCoordinatorHooks(Logger &logger) {
    INSTALL_HOOK(logger, MainMenu);
}

ColoramaInstallHooks(MainFlowCoordinatorHooks)
