#pragma once

#include "Colorama.hpp"

#include "UnityEngine/MonoBehaviour.hpp"
#include "GlobalNamespace/IAudioTimeSource.hpp"
#include "GlobalNamespace/SongProgressUIController.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

DECLARE_CLASS_CODEGEN(Colorama::Coloring, ProgressBarColorizer, MonoBehaviour,
  DECLARE_DEFAULT_CTOR();
  DECLARE_PRIVATE_FIELD(SongProgressUIController*, progressUIController);
  DECLARE_PRIVATE_FIELD(IAudioTimeSource*, audioTimeSyncController);
  DECLARE_INSTANCE_METHOD(void, Construct, SongProgressUIController* progressUIController, IAudioTimeSource* audioTimeSyncController);
  DECLARE_INSTANCE_METHOD(void, Start);
  DECLARE_INSTANCE_METHOD(void, Update);

  public:
    std::vector<UnityEngine::UI::Image*> barComponents = {};
)