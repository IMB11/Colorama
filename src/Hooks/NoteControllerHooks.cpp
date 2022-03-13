#include "Colorama.hpp"

#include "GlobalNamespace/NoteController.hpp"
#include "GlobalNamespace/NoteData.hpp"
#include "GlobalNamespace/GameNoteController.hpp"

MAKE_HOOK_MATCH(NoteController_Init, &GlobalNamespace::NoteController::Init, void, GlobalNamespace::NoteController* self,
                GlobalNamespace::NoteData* noteData,
                float worldRotation,
                UnityEngine::Vector3 moveStartPos,
                UnityEngine::Vector3 moveEndPos,
                UnityEngine::Vector3 jumpEndPos,
                float moveDuration,
                float jumpDuration,
                float jumpGravity,
                float endRotation,
                float uniformScale) {
    NoteController_Init(self, noteData, worldRotation, moveStartPos, moveEndPos, jumpEndPos, moveDuration, jumpDuration, jumpGravity, endRotation, uniformScale);
    if (getColoramaConfig().Game_Enabled.GetValue() || (!getColoramaConfig().Game_LEnabled.GetValue() && !getColoramaConfig().Game_REnabled.GetValue())) {
        return;
    }

    GlobalNamespace::GameNoteController* gameNoteController = reinterpret_cast<GlobalNamespace::GameNoteController*>(self);
}

void NoteControllerHooks(Logger& logger) {
    INSTALL_HOOK(logger, NoteController_Init);
}

ColoramaInstallHooks(NoteControllerHooks);