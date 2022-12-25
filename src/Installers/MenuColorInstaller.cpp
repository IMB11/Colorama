#include "Installers/MenuColorInstaller.hpp"

#include "lapiz/shared/utilities/ZenjectExtensions.hpp"

#include "Coloring/Services/ColorizerService.hpp"
#include "Coloring/Services/DefaultMenuService.hpp"

#include "Zenject/ConcreteIdBinderGeneric_1.hpp"
#include "Zenject/DiContainer.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"

DEFINE_TYPE(Colorama, MenuColorInstaller)

using namespace Colorama::Coloring::Services;

void Colorama::Installers::MenuColorInstaller::InstallBindings() {
  auto container = get_Container();

  container->Bind<ColorizerService*>()->To<DefaultMenuService*>()->AsSingle();
}