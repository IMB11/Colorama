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
    ColorSO *createColorSO(const Color color) {
        const auto so = ScriptableObject::CreateInstance<SimpleColorSO *>();
        so->color = color;
        return so;
    }

    MenuLightsPresetSO *createMenuLights(const Color color) {
        const auto colorSO = createColorSO(color);
        const auto menuPresetSO = Object::Instantiate(defaultLights);
        auto colorPairs = menuPresetSO->lightIdColorPairs;
        for (int i = 0; i < colorPairs.Length(); ++i) {
            const auto pair = MenuLightsPresetSO::LightIdColorPair::
                New_ctor();
            pair->lightId = colorPairs[i]->lightId;
            pair->baseColor = colorSO;
            pair->intensity = colorPairs[i]->intensity;
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
        defaultLights = self->menuLightsManager->defaultPreset;
    }

    mfc = self->menuLightsManager;

    const auto soloFreeplay = self->soloFreePlayFlowCoordinator;
    const auto partyFreeplay = self->partyFreePlayFlowCoordinator;
    const auto campaignCoordinator = self->campaignFlowCoordinator;

    getLogger().info("MainFlowCoordinator::DidActivate - Begin Inject");

    if (getColoramaConfig().Enabled.GetValue()) {
        GameObject::Find("PlayersPlace")
            ->GetComponentInChildren<SpriteRenderer *>()
            ->set_color(getColoramaConfig().Menu_FeetColor.GetValue());

        if (GameObject *menuEnvCore = GameObject::Find("DefaultMenuEnvironment")) {
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

        self->defaultLightsPreset =
            createMenuLights(getColoramaConfig().Menu_GamemodeColor.GetValue());
        soloFreeplay->defaultLightsPreset =
            createMenuLights(getColoramaConfig().Menu_FreeplayColor.GetValue());
        partyFreeplay->defaultLightsPreset =
            createMenuLights(getColoramaConfig().Menu_FreeplayColor.GetValue());
        soloFreeplay->resultsClearedLightsPreset =
            createMenuLights(getColoramaConfig().Menu_ResultsColor.GetValue());
        partyFreeplay->resultsClearedLightsPreset =
            createMenuLights(getColoramaConfig().Menu_ResultsColor.GetValue());
        campaignCoordinator->resultsClearedLightsPreset =
            createMenuLights(getColoramaConfig().Menu_ResultsColor.GetValue());
        campaignCoordinator->resultsFailedLightsPreset =
            createMenuLights(
                getColoramaConfig().Menu_ResultsFailColor.GetValue());
        soloFreeplay->resultsFailedLightsPreset = createMenuLights(
            getColoramaConfig().Menu_ResultsFailColor.GetValue());
        partyFreeplay->resultsFailedLightsPreset = createMenuLights(
            getColoramaConfig().Menu_ResultsFailColor.GetValue());
        campaignCoordinator->defaultLightsPreset = createMenuLights(
            getColoramaConfig().Menu_CampaignsColor.GetValue());

    } else {
        if (GameObject *menuEnvCore =
                GameObject::Find("DefaultMenuEnvironment")) {
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

        self->defaultLightsPreset = defaultLights;

        soloFreeplay->defaultLightsPreset = defaultLights;

        partyFreeplay->defaultLightsPreset = defaultLights;

        soloFreeplay->resultsClearedLightsPreset = defaultLights;

        partyFreeplay->resultsClearedLightsPreset = defaultLights;

        campaignCoordinator->resultsClearedLightsPreset = defaultLights;

        campaignCoordinator->resultsFailedLightsPreset =
            createMenuLights(Color::get_red());

        soloFreeplay->resultsFailedLightsPreset =
            createMenuLights(Color::get_red());

        partyFreeplay->resultsFailedLightsPreset =
            createMenuLights(Color::get_red());

        campaignCoordinator->defaultLightsPreset = defaultLights;
    }

    getLogger().info("MainFlowCoordinator::DidActivate - End Inject");
    MainMenu(self, a, b, c);
}

void MainFlowCoordinatorHooks(Logger &logger) {
    INSTALL_HOOK(logger, MainMenu);
}

ColoramaInstallHooks(MainFlowCoordinatorHooks)
