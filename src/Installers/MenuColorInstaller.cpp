#include "Installers/MenuColorInstaller.hpp"

#include "Coloring/Services/ColorizerService.hpp"
#include "Coloring/Services/DefaultMenuService.hpp"
#include "UI/ColoramaFlowCoordinator.hpp"
#include "UI/MenuButtonManager.hpp"
#include "UI/Views/InfoViewController.hpp"
#include "Zenject/ConcreteIdBinderGeneric_1.hpp"
#include "Zenject/DiContainer.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"
#include "lapiz/shared/utilities/ZenjectExtensions.hpp"

DEFINE_TYPE(Colorama::Installers, MenuColorInstaller)

using namespace Colorama::Coloring::Services;
using namespace Colorama::UI;

void Colorama::Installers::MenuColorInstaller::InstallBindings() {
  auto container = get_Container();

  Lapiz::Zenject::ZenjectExtensions::FromNewComponentOnNewGameObject(
      container->Bind<ColoramaFlowCoordinator*>())
      ->AsSingle();
  Lapiz::Zenject::ZenjectExtensions::FromNewComponentAsViewController(
      container->Bind<InfoViewController*>())
      ->AsSingle();

  container->BindInterfacesAndSelfTo<MenuButtonManager*>()->AsSingle();
  //  container->Bind<ColorizerService*>()->To<DefaultMenuService*>()->AsSingle();
}