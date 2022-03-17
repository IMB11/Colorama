#pragma once

#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "modloader/shared/modloader.hpp"
#include "custom-types/shared/macros.hpp"

#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "GlobalNamespace/MenuLightsPresetSO.hpp"
#include "GlobalNamespace/MenuLightsManager.hpp"
#include "GlobalNamespace/ColorSO.hpp"
#include "GlobalNamespace/SimpleColorSO.hpp"
#include "UnityEngine/ScriptableObject.hpp"
#include "GlobalNamespace/MenuLightsPresetSO_LightIdColorPair.hpp"
#include "UnityEngine/SpriteRenderer.hpp"

#include "ColoramaConfig.hpp"

static ModInfo modInfo;
static GlobalNamespace::MenuLightsPresetSO* defaultLights;
static GlobalNamespace::MenuLightsManager *mfc;

Configuration& getConfig();
Logger &getLogger();

namespace Colorama {
    class Hooks {
      private:
        inline static std::vector<void (*)(Logger &logger)> installFuncs;

      public:
        static void AddInstallFunc(void (*installFunc)(Logger &logger)) {
            installFuncs.push_back(installFunc);
        }

        static void InstallHooks(Logger &logger) {
            for (auto installFunc : installFuncs) {
                installFunc(logger);
            }
        }
    };
} // namespace Colorama

#define ColoramaInstallHooks(func)                                             \
    struct __ColoramaRegister##func {                                          \
        __ColoramaRegister##func() { Colorama::Hooks::AddInstallFunc(func); }  \
    };                                                                         \
    static __ColoramaRegister##func __ColoramaRegisterInstance##func;