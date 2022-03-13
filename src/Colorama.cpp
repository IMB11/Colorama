#include "Colorama.hpp"

DEFINE_CONFIG(ColoramaConfig);

extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
    getConfig().Load();
    getLogger().info("Completed setup!");
}

extern "C" void load() {
    il2cpp_functions::Init();

    getColoramaConfig().Init(modInfo);

    getLogger().info("Installing hooks...");
    Colorama::Hooks::InstallHooks(getLogger());
    getLogger().info("Installed all hooks!");
}