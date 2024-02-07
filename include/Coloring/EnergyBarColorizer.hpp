#pragma once

#include "Colorama.hpp"
#include "GlobalNamespace/GameEnergyUIPanel.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "custom-types/shared/delegate.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

DECLARE_CLASS_CODEGEN(
    Colorama::Coloring, EnergyBarColorizer, MonoBehaviour,
    DECLARE_DEFAULT_CTOR();
    DECLARE_PRIVATE_FIELD(GameEnergyUIPanel*, energyPanel);
    DECLARE_PRIVATE_FIELD(UI::Image*, mainImage);

    DECLARE_INSTANCE_METHOD(void, Construct, GameEnergyUIPanel* energyPanel);
    DECLARE_INSTANCE_METHOD(void, Update); DECLARE_INSTANCE_METHOD(void, Start);
    DECLARE_INSTANCE_METHOD(void, HandleEnergyChange, float energy);

    public
    : custom_types::Helpers::Coroutine PrepareColors();)