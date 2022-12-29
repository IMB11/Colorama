#include "Installers/ZenjectInstallers.hpp"

#include "Coloring/MenuColorSwapper.hpp"
#include "Coloring/ComboModifierHelper.hpp"

#include "UI/ColoramaFlowCoordinator.hpp"
#include "UI/MenuButtonManager.hpp"
#include "UI/Views/ConfigViewController.hpp"
#include "UI/Views/PreviewViewController.hpp"
#include "UI/Views/InfoViewController.hpp"

#include "Zenject/ConcreteIdBinderGeneric_1.hpp"
#include "Zenject/DiContainer.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"

#include "lapiz/shared/utilities/ZenjectExtensions.hpp"

DEFINE_TYPE(Colorama::Installers, MenuColorInstaller)
DEFINE_TYPE(Colorama::Installers, PanelModifierInstaller)

using namespace Colorama::UI;
using namespace Colorama::Coloring;
using namespace Colorama::Installers;

void MenuColorInstaller::InstallBindings() {
  auto container = get_Container();

  Lapiz::Zenject::ZenjectExtensions::FromNewComponentOnNewGameObject(
      container->Bind<ColoramaFlowCoordinator*>())
      ->AsSingle();
  Lapiz::Zenject::ZenjectExtensions::FromNewComponentAsViewController(
      container->Bind<InfoViewController*>())
      ->AsSingle();
  Lapiz::Zenject::ZenjectExtensions::FromNewComponentAsViewController(
      container->Bind<ConfigViewController*>())
      ->AsSingle();
  Lapiz::Zenject::ZenjectExtensions::FromNewComponentAsViewController(
      container->Bind<PreviewViewController*>())
      ->AsSingle();

  container->BindInterfacesAndSelfTo<MenuButtonManager*>()->AsSingle();

  container->BindInterfacesAndSelfTo<MenuColorSwapper*>()->AsSingle();
}

void PanelModifierInstaller::InstallBindings() {
  auto container = get_Container();

  Lapiz::Zenject::ZenjectExtensions::FromNewComponentOnNewGameObject(
      container->Bind<ComboModifierHelper*>())
      ->AsSingle();
}
