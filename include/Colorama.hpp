#pragma once

#include <string_view>

#include "ColoramaConfig.hpp"
#include "ColoramaHooks.hpp"
#include "ColoramaMacros.hpp"
#include "GlobalNamespace/MenuLightsManager.hpp"
#include "GlobalNamespace/MenuLightsPresetSO.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "modloader/shared/modloader.hpp"
#include "paper/shared/logger.hpp"

static ModInfo modInfo;

Logger &getLogger();

#define LOG(...) INFO(__VA_ARGS__);
#define INFO(...) Paper::Logger::fmtLog<Paper::LogLevel::INF>(__VA_ARGS__);
#define ERROR(...) Paper::Logger::fmtLog<Paper::LogLevel::ERR>(__VA_ARGS__);
#define CRITICAL(...) Paper::Logger::fmtLog<Paper::LogLevel::ERR>(__VA_ARGS__);
#define DEBUG(...) Paper::Logger::fmtLog<Paper::LogLevel::DBG>(__VA_ARGS__);