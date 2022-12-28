#pragma once

#include <string>

#include "UnityEngine/Color.hpp"
#include "config-utils/shared/config-utils.hpp"

using namespace UnityEngine;

#define ENABLE_COLOR_CONFIG_VALUE(name, desc)  \
  CONFIG_VALUE(Can_##name, bool, "Can" desc, false); \
  CONFIG_VALUE(name, ConfigUtils::Color, desc, \
               static_cast<ConfigUtils::Color>(Color::get_red()));

// clang-format off
DECLARE_CONFIG(ColoramaConfig,
    ENABLE_COLOR_CONFIG_VALUE(Menu_GamemodeColor, "Gamemode Selection Menu Color");
    ENABLE_COLOR_CONFIG_VALUE(Menu_FreeplayColor, "Solo/Party Menu Color");
    ENABLE_COLOR_CONFIG_VALUE(Menu_ResultsColor, "Results Menu Color");
    ENABLE_COLOR_CONFIG_VALUE(Menu_ResultsFailColor, "Fail Menu Color");
    ENABLE_COLOR_CONFIG_VALUE(Menu_CampaignsColor, "Campaign Menu Color");
    ENABLE_COLOR_CONFIG_VALUE(Menu_FeetColor, "Feet Indicator Color");
	ENABLE_COLOR_CONFIG_VALUE(Menu_MultiplayerColor, "Multiplayer Lobby Color");
	ENABLE_COLOR_CONFIG_VALUE(Menu_MultiplayerCountdownColor, "Multiplayer Lobby Countdown Color");

    CONFIG_VALUE(Menu_MenuFogRing, bool, "Menu Fog Ring", true);
    CONFIG_VALUE(Menu_Notes, bool, "Menu Notes", true);
    CONFIG_VALUE(Menu_LogoGlowLines, bool, "Logo Glow Lines", false);
    CONFIG_VALUE(Menu_MenuGround, bool, "Menu Ground", true);
)
// clang-format on