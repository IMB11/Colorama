#include "Colorama.hpp"

#include "questui/shared/QuestUI.hpp"
#include "UI/CFlowCoordinator.hpp"

DEFINE_CONFIG(ColoramaConfig);

Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger &getLogger() {
    static Logger *logger = new Logger(modInfo);
    return *logger;
}

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

    custom_types::Register::AutoRegister();

    QuestUI::Init();
    QuestUI::Register::RegisterMainMenuModSettingsFlowCoordinator<Colorama::UI::CFlowCoordinator*>(modInfo);
}