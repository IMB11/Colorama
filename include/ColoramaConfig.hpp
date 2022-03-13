#pragma once

#include "config-utils/shared/config-utils.hpp"
#include "UnityEngine/Color.hpp"

using namespace UnityEngine;

// clang-format off
DECLARE_CONFIG(ColoramaConfig,
    CONFIG_VALUE(Game_Enabled, bool, "Game_Enabled", false)
    CONFIG_VALUE(Game_LEnabled, bool, "Game_LEnabled", false)
    CONFIG_VALUE(Game_REnabled, bool, "Game_REnabled", false)
    CONFIG_VALUE(Game_LColor, Color, "Game_LColor", Color::get_white())
    CONFIG_VALUE(Game_RColor, Color, "Game_RColor", Color::get_white())

    CONFIG_VALUE(Menu_Enabled, bool, "Menu_Enabled", true)
    CONFIG_VALUE(Menu_DefaultColor, Color, "Menu_DefaultColor", Color::get_cyan())

    CONFIG_VALUE(Menu_FreeplayColor, Color, "Menu_FreeplayColor", Color::get_white())
    CONFIG_VALUE(Menu_ResultsColor, Color, "Menu_ResultsColor", Color::get_white())
    CONFIG_VALUE(Menu_ResultsFailColor, Color, "Menu_ResultsFailColor", Color::get_white())
    CONFIG_VALUE(Menu_CampaignsColor, Color, "Menu_CampaignsColor", Color::get_white())
    CONFIG_VALUE(Menu_FeetColor, Color, "Menu_FeetColor", Color::get_white())
    CONFIG_VALUE(Menu_MultiplayerColor, Color, "Menu_MultiplayerColor", Color::get_white())
    CONFIG_VALUE(Menu_MultiplayerCountdownColor, Color, "Menu_MultiplayerCountdownColor", Color::get_white())

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(Game_Enabled)
        CONFIG_INIT_VALUE(Game_LEnabled)
        CONFIG_INIT_VALUE(Game_REnabled)
        CONFIG_INIT_VALUE(Game_RColor)
        CONFIG_INIT_VALUE(Game_LColor)

        CONFIG_INIT_VALUE(Menu_Enabled)
        CONFIG_INIT_VALUE(Menu_DefaultColor)

        CONFIG_INIT_VALUE(Menu_FreeplayColor)
        CONFIG_INIT_VALUE(Menu_ResultsColor)
        CONFIG_INIT_VALUE(Menu_ResultsFailColor)
        CONFIG_INIT_VALUE(Menu_CampaignsColor)
        CONFIG_INIT_VALUE(Menu_FeetColor)
        CONFIG_INIT_VALUE(Menu_MultiplayerColor)
        CONFIG_INIT_VALUE(Menu_MultiplayerCountdownColor)
    )
)
// clang-format on