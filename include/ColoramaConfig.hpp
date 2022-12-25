#pragma once

#include "UnityEngine/Color.hpp"
#include "config-utils/shared/config-utils.hpp"

#include <string>

using namespace UnityEngine;

// clang-format off
DECLARE_CONFIG(ColoramaConfig,
    CONFIG_VALUE(Enabled, bool, "Colorama Enabled", false);
    CONFIG_VALUE(Menu_GamemodeColor, ConfigUtils::Color, "Gamemode Selection Menu Color", static_cast<ConfigUtils::Color>(Color::get_cyan()));
    CONFIG_VALUE(Menu_FreeplayColor, ConfigUtils::Color, "Solo/Party Menu Color", static_cast<ConfigUtils::Color>(Color::get_cyan()));
    CONFIG_VALUE(Menu_ResultsColor, ConfigUtils::Color, "Results Menu Color", static_cast<ConfigUtils::Color>(Color::get_cyan()));
    CONFIG_VALUE(Menu_ResultsFailColor, ConfigUtils::Color, "Fail Menu Color", static_cast<ConfigUtils::Color>(Color::get_cyan()));
    CONFIG_VALUE(Menu_CampaignsColor, ConfigUtils::Color, "Campaign Menu Color", static_cast<ConfigUtils::Color>(Color::get_cyan()));
    CONFIG_VALUE(Menu_FeetColor, ConfigUtils::Color, "Feet Indicator Color", static_cast<ConfigUtils::Color>(Color::get_cyan()));

    CONFIG_VALUE(Menu_MenuFogRing, bool, "Menu Fog Ring", true);
    CONFIG_VALUE(Menu_Notes, bool, "Menu Notes", true);
    CONFIG_VALUE(Menu_LogoGlowLines, bool, "Logo Glow Lines", false);
    CONFIG_VALUE(Menu_MenuGround, bool, "Menu Ground", true);
)
// clang-format on