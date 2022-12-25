#include "Colorama.hpp"


#include "lapiz/shared/zenject/Zenjector.hpp"
#include "Installers/MenuColorInstaller.hpp"
#include "questui/shared/QuestUI.hpp"

#include "UI/ColoramaFlowCoordinator.hpp"

// Returns a logger, useful for printing debug messages
Logger &getLogger() {
  static Logger *logger = new Logger(modInfo);
  return *logger;
}

extern "C" void setup(ModInfo &info) {
  info.id = MOD_ID;
  info.version = VERSION;
  modInfo = info;
  getColoramaConfig().Init(modInfo);
  getLogger().info("Completed setup!");
}

extern "C" void load() {
  il2cpp_functions::Init();
  custom_types::Register::AutoRegister();

  getLogger().info("Preparing Zenject");

  auto zenjector = ::Lapiz::Zenject::Zenjector::Get();
  zenjector->Install<Colorama::Installers::MenuColorInstaller*>(Lapiz::Zenject::Location::Menu);

  getLogger().info("Completed Zenject");


  getLogger().info("Installing hooks...");

//  Colorama::Hooks::InstallHooks(getLogger());

  getLogger().info("Installed all hooks!");

  QuestUI::Init();
}