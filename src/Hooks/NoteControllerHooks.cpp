//#include "Colorama.hpp"
//
//#include "GlobalNamespace/NoteController.hpp"
//#include "GlobalNamespace/NoteData.hpp"
//#include "GlobalNamespace/GameNoteController.hpp"
//#include "GlobalNamespace/ColorType.hpp"
//#include "UnityEngine/Color.hpp"
//#include "GlobalNamespace/ColorNoteVisuals.hpp"
//#include "UnityEngine/MeshRenderer.hpp"
//
//MAKE_HOOK_MATCH(NoteController_Init, &GlobalNamespace::NoteController::Init, void, GlobalNamespace::NoteController* self,
//                GlobalNamespace::NoteData* noteData,
//                float worldRotation,
//                UnityEngine::Vector3 moveStartPos,
//                UnityEngine::Vector3 moveEndPos,
//                UnityEngine::Vector3 jumpEndPos,
//                float moveDuration,
//                float jumpDuration,
//                float jumpGravity,
//                float endRotation,
//                float uniformScale,
//                bool rotateTowardsPlayer,
//                bool useRandomRotation) {
//    NoteController_Init(self, noteData, worldRotation, moveStartPos, moveEndPos, jumpEndPos, moveDuration, jumpDuration, jumpGravity, endRotation, uniformScale, rotateTowardsPlayer, useRandomRotation);
//
//    if (!getColoramaConfig().Enabled.GetValue() || (!getColoramaConfig().Game_LEnabled.GetValue() && !getColoramaConfig().Game_REnabled.GetValue())) {
//        return;
//    }
//
//    getLogger().info("Game Enabled");
//
//    if(GlobalNamespace::GameNoteController* gameNoteController = il2cpp_utils::try_cast<GlobalNamespace::GameNoteController>(self).value()) {
//        getLogger().info("Successful Cast");
//        auto colorType = gameNoteController->get_noteData()->get_colorType();
//
//        if(colorType == GlobalNamespace::ColorType::_get_ColorA() && !getColoramaConfig().Game_LEnabled.GetValue()) {
//            return;
//        }
//        if(colorType == GlobalNamespace::ColorType::_get_ColorB() && !getColoramaConfig().Game_REnabled.GetValue()) {
//            return;
//        }
//
//        UnityEngine::Color dynamicColor = colorType == GlobalNamespace::ColorType::_get_ColorA() ? getColoramaConfig().Game_LColor.GetValue() : getColoramaConfig().Game_RColor.GetValue();
//
//        getLogger().info("Color: %s", static_cast<std::string>(dynamicColor.ToString()).c_str());
//
//        auto visuals = gameNoteController->GetComponent<GlobalNamespace::ColorNoteVisuals*>();
//
//        for (auto mesh : visuals->dyn__arrowMeshRenderers()) {
//            mesh->get_material()->set_color(dynamicColor);
//        }
//
//        for (auto mesh : visuals->dyn__arrowMeshRenderers()) {
//            mesh->get_material()->set_color(dynamicColor);
//        }
//    }
//}
//
//void NoteControllerHooks(Logger& logger) {
//    INSTALL_HOOK(logger, NoteController_Init);
//}
//
//ColoramaInstallHooks(NoteControllerHooks);