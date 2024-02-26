#include "Colorama.hpp"

#include "Installers/ZenjectInstallers.hpp"
#include "UI/ColoramaFlowCoordinator.hpp"
#include "lapiz/shared/zenject/Zenjector.hpp"
#include "questui/shared/QuestUI.hpp"

// Returns a logger, useful for printing debug messages
Logger &getLogger() {
  static Logger *logger = new Logger(modInfo);
  return *logger;
}

extern "C" void setup(ModInfo &info) {
  info.id      = MOD_ID;
  info.version = VERSION;
  modInfo      = info;
  INFO("Completed setup!");
}

extern "C" void load() {
  using namespace Colorama::Installers;
  using namespace ::Lapiz::Zenject;

  il2cpp_functions::Init();
  custom_types::Register::AutoRegister();
  ::Lapiz::Attributes::AutoRegister();

  getColoramaConfig().Init(modInfo);

  INFO("Preparing Zenject");

  auto zenjector = Zenjector::Get();

  // zenjector->Expose<GlobalNamespace::ComboUIController*>("Environment");

  zenjector->Install<MenuColorInstaller *>(Location::Menu);

  INFO("Completed Zenject");

  INFO("Installing hooks...");

  Colorama::Hooks::InstallHooks(getLogger());

  INFO("Installed all hooks!");

  QuestUI::Init();
}