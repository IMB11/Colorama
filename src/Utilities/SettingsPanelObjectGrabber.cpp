#include "Utilities/SettingsPanelObjectGrabber.hpp"

DEFINE_TYPE(Colorama::Utilities, SettingsPanelObjectGrabber);

using namespace Colorama::Utilities;
using namespace GlobalNamespace;
using namespace UnityEngine;

void SettingsPanelObjectGrabber::Start() {
  this->isCompleted = false;
  StartCoroutine(custom_types::Helpers::CoroutineHelper::New(GrabPanels()));
}

#include "UnityEngine/SceneManagement/SceneManager.hpp"
#include "UnityEngine/AsyncOperation.hpp"
#include "UnityEngine/WaitForSecondsRealtime.hpp"
#include "UnityEngine/Resources.hpp"

#include "System/Collections/IEnumerator.hpp"

#include "GlobalNamespace/ScoreMultiplierUIController.hpp"
#include "GlobalNamespace/GameEnergyUIPanel.hpp"
#include "GlobalNamespace/ComboUIController.hpp"
#include "GlobalNamespace/SongProgressUIController.hpp"
#include "GlobalNamespace/ImmediateRankUIPanel.hpp"

using namespace UnityEngine::SceneManagement;

custom_types::Helpers::Coroutine SettingsPanelObjectGrabber::GrabPanels() {
  bool isSceneLoaded = false;
  AsyncOperation* loadScene = SceneManager::LoadSceneAsync("DefaultEnvironment", LoadSceneMode::_get_Additive());
  while(!loadScene->get_isDone()) co_yield nullptr;
  isSceneLoaded = true;
  co_yield reinterpret_cast<System::Collections::IEnumerator*>(WaitForSecondsRealtime::New_ctor(0.1f));

  std::vector<MonoBehaviour*> _controllers = {
      Resources::FindObjectsOfTypeAll<ScoreMultiplierUIController*>().FirstOrDefault(),
      Resources::FindObjectsOfTypeAll<GameEnergyUIPanel*>().FirstOrDefault(),
      Resources::FindObjectsOfTypeAll<ComboUIController*>().FirstOrDefault(),
      Resources::FindObjectsOfTypeAll<SongProgressUIController*>().FirstOrDefault(),
      Resources::FindObjectsOfTypeAll<ImmediateRankUIPanel*>().FirstOrDefault(),
  };

  multiplierPanel = FinalizePanel(_controllers[0]);
  energyPanel = FinalizePanel(_controllers[1]);
  comboPanel = FinalizePanel(_controllers[2]);
  progressPanel = FinalizePanel(_controllers[3]);
  immediateRankPanel = FinalizePanel(_controllers[4]);

  if(multiplierPanel && energyPanel && comboPanel && progressPanel && immediateRankPanel)  {
	this->isCompleted = true;
  }

  loadScene = nullptr;
  SceneManager::UnloadSceneAsync("DefaultEnvironment");
  co_return;
}

UnityEngine::GameObject *SettingsPanelObjectGrabber::FinalizePanel(UnityEngine::MonoBehaviour *controller) {
  auto go = Instantiate(controller->get_gameObject());
  Destroy(go->GetComponent(controller->GetType()));
  go->get_transform()->SetParent(get_transform());
  go->get_transform()->set_localPosition(Vector3::get_zero());
  go->get_transform()->set_localRotation(Quaternion::get_identity());
  return go;
}