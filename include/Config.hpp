#pragma once

#include <optional>
#include <string>

using std::optional;
using std::string;

namespace ox {

enum ConfigStart { CROSS, CIRCLE };

enum ConfigBotTactic { HEURISTIC, GAME_TREE };

enum ConfigUiSize { SMALL, MEDIUM, LARGE };

struct Config {
    bool cross_is_bot;
    bool circle_is_bot;
    ConfigStart start;
    ConfigBotTactic bot_tactic;
    ConfigUiSize ui_size;
    int depth;

    static std::optional<Config> try_from_script(const char* config_string);
};

}
