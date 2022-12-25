#pragma once

#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "custom-types/shared/macros.hpp"
#include "modloader/shared/modloader.hpp"

#include "GlobalNamespace/MenuLightsManager.hpp"
#include "GlobalNamespace/MenuLightsPresetSO.hpp"

#include "ColoramaConfig.hpp"

static ModInfo modInfo;

Logger &getLogger();

#define DECLARE_OVERRIDE_METHOD_MATCH(retval, name, mptr, ...) \
    DECLARE_OVERRIDE_METHOD(retval, name, il2cpp_utils::il2cpp_type_check::MetadataGetter<mptr>::get(), __VA_ARGS__)

template <class T, class U >
bool is_inst(U u) {
  return il2cpp_utils::try_cast<T>(u).has_value();
}

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
  struct __ColoramaRegister##func {                                            \
    __ColoramaRegister##func() { Colorama::Hooks::AddInstallFunc(func); }      \
  };                                                                           \
  static __ColoramaRegister##func __ColoramaRegisterInstance##func;