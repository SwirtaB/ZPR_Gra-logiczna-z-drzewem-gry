#pragma once

#include "Utils.hpp"
#include "Field.hpp"
#include "Config.hpp"

namespace ox::bot
{
    /// Zwraca ruch wykonywany przez bota za pomocą podanej taktyki.
    std::pair<int, int> bot_move(const FieldBoard &, PlayerEnum, ConfigBotTactic, int depth);
}
