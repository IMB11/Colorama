#pragma once

#include "config-utils/shared/config-utils.hpp"
#include "UnityEngine/Color.hpp"

using namespace UnityEngine;

// clang-format off
DECLARE_CONFIG(ColoramaConfig,
    CONFIG_VALUE(Enabled, bool, "Colorama Enabled", false)
    CONFIG_VALUE(Menu_GamemodeColor, Color, "Gamemode Selection Menu Color", Color::get_white())
    CONFIG_VALUE(Menu_FreeplayColor, Color, "Solo/Party Menu Color", Color::get_white())
    CONFIG_VALUE(Menu_ResultsColor, Color, "Results Menu Color", Color::get_white())
    CONFIG_VALUE(Menu_ResultsFailColor, Color, "Fail Menu Color", Color::get_white())
    CONFIG_VALUE(Menu_CampaignsColor, Color, "Campaign Menu Color", Color::get_white())
    CONFIG_VALUE(Menu_FeetColor, Color, "Feet Indicator Color", Color::get_white())

    CONFIG_VALUE(Menu_MenuFogRing, bool, "Menu Fog Ring", true);
    CONFIG_VALUE(Menu_Notes, bool, "Menu Notes", true);
    CONFIG_VALUE(Menu_LogoGlowLines, bool, "Logo Glow Lines", false);
    CONFIG_VALUE(Menu_MenuGround, bool, "Menu Ground", true);

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(Enabled)

        CONFIG_INIT_VALUE(Menu_FreeplayColor)
        CONFIG_INIT_VALUE(Menu_GamemodeColor)
        CONFIG_INIT_VALUE(Menu_ResultsColor)
        CONFIG_INIT_VALUE(Menu_ResultsFailColor)
        CONFIG_INIT_VALUE(Menu_CampaignsColor)
        CONFIG_INIT_VALUE(Menu_FeetColor)

        CONFIG_INIT_VALUE(Menu_MenuFogRing)
        CONFIG_INIT_VALUE(Menu_Notes)
        CONFIG_INIT_VALUE(Menu_LogoGlowLines)
        CONFIG_INIT_VALUE(Menu_MenuGround)
    )
)
// clang-format on