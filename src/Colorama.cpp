#include "Colorama.hpp"

#include "Installers/MenuColorInstaller.hpp"
#include "UI/ColoramaFlowCoordinator.hpp"
#include "lapiz/shared/zenject/Zenjector.hpp"
#include "questui/shared/QuestUI.hpp"

// Returns a logger, useful for printing debug messages
Logger &getLogger() {
  static Logger *logger = new Logger(modInfo);
  return *logger;
}

extern "C" void setup(ModInfo &info) {
  info.id = MOD_ID;
  info.version = VERSION;
  modInfo = info;
  INFO("Completed setup!");
}

extern "C" void load() {
  il2cpp_functions::Init();
  custom_types::Register::AutoRegister();

  getColoramaConfig().Init(modInfo);

  INFO("Preparing Zenject");
  auto zenjector = ::Lapiz::Zenject::Zenjector::Get();
  zenjector->Install<Colorama::Installers::MenuColorInstaller *>(
      Lapiz::Zenject::Location::Menu);

  INFO("Completed Zenject");

  INFO("Installing hooks...");

  Colorama::Hooks::InstallHooks(getLogger());

  INFO("Installed all hooks!");

  QuestUI::Init();
}