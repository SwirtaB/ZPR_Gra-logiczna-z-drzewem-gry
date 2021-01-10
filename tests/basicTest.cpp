//
// Created by swirta on 20.11.2020.
//

#define BOOST_TEST_MODULE ClassTests

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include "../include/Controller.hpp"

#include <fstream>
#include <iostream>

#include <boost/python.hpp>

namespace py = boost::python;

using namespace ox;

BOOST_AUTO_TEST_CASE(boost_python_test)
{
    std::cout << "---BOOST.PYTHON TEST---" << std::endl;
    Py_Initialize();
    py::object main_module = py::import("__main__");
    py::object main_namespace = main_module.attr("__dict__");
    int res = 0;
    try
    {
        py::object noneType = py::exec("res = 3", main_namespace);
        res = py::extract<int>(main_namespace["res"]);
    }
    catch (py::error_already_set const &)
    {
        PyErr_Print();
    }
    BOOST_CHECK_EQUAL(res, 3);
}

BOOST_AUTO_TEST_CASE(python_config_read_test)
{
    std::cout << "---PYTHON CONFIG READ TEST---" << std::endl;
    std::ifstream ifs = std::move(std::ifstream("no_file_test_config.py"));
    std::string no_file_config_string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    std::optional<Config> o_config = Config::try_from_script(no_file_config_string.c_str());
    BOOST_REQUIRE_EQUAL(o_config.has_value(), 0);

    ifs = std::move(std::ifstream("worng_data_file_test_config.py"));
    std::string worng_data_config_string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    o_config = Config::try_from_script(no_file_config_string.c_str());
    BOOST_REQUIRE_EQUAL(o_config.has_value(), 0);

    ifs = std::move(std::ifstream("test_config.py"));
    std::string config_string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    o_config = Config::try_from_script(config_string.c_str());

    BOOST_REQUIRE_EQUAL(o_config.value().bot_tactic, GAME_TREE);
    BOOST_REQUIRE_EQUAL(o_config.value().depth, 10);
    BOOST_REQUIRE_EQUAL(o_config.value().start, CROSS);
    BOOST_REQUIRE_EQUAL(o_config.value().circle_is_bot, 1);
    BOOST_REQUIRE_EQUAL(o_config.value().cross_is_bot, 0);
    BOOST_REQUIRE_EQUAL(o_config.value().save_path, "save.txt");
    BOOST_REQUIRE_EQUAL(o_config.value().ui_size, SMALL);
}

BOOST_AUTO_TEST_CASE(game_test)
{
    std::cout << "---GAME TEST---" << std::endl;
    std::shared_ptr<MessageQueues> testQueuesHandler = std::make_shared<MessageQueues>();

    Config config;
    config.start = ConfigStart::CIRCLE;
    config.circle_is_bot = false;
    config.cross_is_bot = false;

    Controller game(config, testQueuesHandler);
    testQueuesHandler->send_player_input(PlayerInputMessage(INPUT, 1, 1));
    testQueuesHandler->send_player_input(PlayerInputMessage(INPUT, 1, 0));
    testQueuesHandler->send_player_input(PlayerInputMessage(INPUT, 0, 0));
    testQueuesHandler->send_player_input(PlayerInputMessage(INPUT, 0, 2));
    testQueuesHandler->send_player_input(PlayerInputMessage(INPUT, 2, 2));
    testQueuesHandler->send_player_input(PlayerInputMessage(EXIT, 0, 0));
    game.run();

    int recieved = 0;
    while (recieved < 6)
    {
        std::optional<GameStateMessage> gs = testQueuesHandler->check_for_game_state();
        if (gs)
        {
            if (recieved == 0)
            {
                BOOST_CHECK_EQUAL(gs.value().gameStateEnum, PREPARING);
            }
            else
            {
                BOOST_CHECK_EQUAL(gs.value().gameStateEnum, PLAYING);
            }
            ++recieved;
        }
    }

    std::optional<GameStateMessage> last_gs;
    do
    {
        last_gs = testQueuesHandler->check_for_game_state();
    } while (!last_gs);
    BOOST_CHECK_EQUAL(last_gs.value().gameStateEnum, CIRCLE_WON);
}