#include "../include/Config.hpp"

#include <optional>
#include <string>

#include <fstream>

#include <boost/python.hpp>
namespace py = boost::python;

using namespace ox;

std::optional<Config> Config::try_from_script(const char* config_str) {
    Py_Initialize();
    py::object main_module = py::import("__main__");
    py::object main_namespace = main_module.attr("__dict__");
    try {

        py::object noneType = py::exec(config_str, main_namespace);
        
        Config config;

        config.cross_is_bot = py::extract<bool>(main_namespace["cross_is_bot"]);
        config.circle_is_bot = py::extract<bool>(main_namespace["circle_is_bot"]);

        char* start_text = py::extract<char*>(main_namespace["start"]);
        if (string("cross") == start_text) {
            config.start = ConfigStart::CROSS;
        } else if (string("circle") == start_text) {
            config.start = ConfigStart::CIRCLE;
        } else {
            return std::optional<Config>();
        }

        char* bot_tactic = py::extract<char*>(main_namespace["bot_tactic"]);
        if (string("heuristic") == bot_tactic) {
            config.bot_tactic = ConfigBotTactic::HEURISTIC;
        } else if (string("game tree") == bot_tactic) {
            config.bot_tactic = ConfigBotTactic::GAME_TREE;
        } else {
            return std::optional<Config>();
        }
        
        char* ui_size = py::extract<char*>(main_namespace["ui_size"]);
        if (string("small") == ui_size) {
            config.ui_size = ConfigUiSize::SMALL;
        } else if (string("medium") == ui_size) {
            config.ui_size = ConfigUiSize::MEDIUM;
        } else if (string("large") == ui_size) {
            config.ui_size = ConfigUiSize::LARGE;
        } else {
            return std::optional<Config>();
        }
        if(config.bot_tactic == GAME_TREE){
            config.depth = py::extract<int>(main_namespace["depth"]);
        }

        return std::optional<Config>(config);

    } catch (py::error_already_set const &) {
        PyErr_Print();
        return std::optional<Config>();
    }
}