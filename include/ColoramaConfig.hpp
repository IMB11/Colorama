#pragma once

#include "config-utils/shared/config-utils.hpp"
#include "UnityEngine/Color.hpp"

using namespace UnityEngine;

// clang-format off
DECLARE_CONFIG(ColoramaConfig,
    CONFIG_VALUE(Game_LEnabled, bool, "Left Arrow Color Enabled", false)
    CONFIG_VALUE(Game_REnabled, bool, "Right Arrow Color Enabled", false)
    CONFIG_VALUE(Game_LColor, Color, "Left Arrow Color", Color::get_white())
    CONFIG_VALUE(Game_RColor, Color, "Right Arrow Color", Color::get_white())

    CONFIG_VALUE(Enabled, bool, "Colorama Enabled", false)
    CONFIG_VALUE(Menu_GamemodeColor, Color, "Gamemode Selection Menu Color", Color::get_white())
    CONFIG_VALUE(Menu_FreeplayColor, Color, "Solo/Party Menu Color", Color::get_white())
    CONFIG_VALUE(Menu_ResultsColor, Color, "Results Menu Color", Color::get_white())
    CONFIG_VALUE(Menu_ResultsFailColor, Color, "Fail Menu Color", Color::get_white())
    CONFIG_VALUE(Menu_CampaignsColor, Color, "Campaign Menu Color", Color::get_white())
    CONFIG_VALUE(Menu_FeetColor, Color, "Feet Indicator Color", Color::get_white())

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(Game_LEnabled)
        CONFIG_INIT_VALUE(Game_REnabled)
        CONFIG_INIT_VALUE(Game_RColor)
        CONFIG_INIT_VALUE(Game_LColor)

        CONFIG_INIT_VALUE(Enabled)

        CONFIG_INIT_VALUE(Menu_FreeplayColor)
        CONFIG_INIT_VALUE(Menu_GamemodeColor)
        CONFIG_INIT_VALUE(Menu_ResultsColor)
        CONFIG_INIT_VALUE(Menu_ResultsFailColor)
        CONFIG_INIT_VALUE(Menu_CampaignsColor)
        CONFIG_INIT_VALUE(Menu_FeetColor)
    )
)
// clang-format on