#pragma once

#include "Utils.hpp"
#include "Field.hpp"
#include "Config.hpp"

namespace ox::bot
{
    std::pair<int, int> bot_move(const FieldBoard &, PlayerEnum, ConfigBotTactic, int depth);
}
