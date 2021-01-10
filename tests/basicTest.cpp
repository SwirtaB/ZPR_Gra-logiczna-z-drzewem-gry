//
// Created by swirta on 20.11.2020.
//

#define BOOST_TEST_MODULE ClassTests

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include "../include/Controller.hpp"

#include <iostream>

#include <boost/python.hpp>
namespace py = boost::python;

using namespace ox;

BOOST_AUTO_TEST_CASE(dummy_test)
{
    std::cout << "---DUMMY TEST---" << std::endl;
    int i = 2;
    i += i;
    BOOST_CHECK_EQUAL(i, 4);
}

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