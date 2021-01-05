//
// Created by swirta on 20.11.2020.
//

#define BOOST_TEST_MODULE ClassTests

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include "../include/Model.hpp"

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
    try {
        py::object noneType = py::exec("res = 3", main_namespace);
        res = py::extract<int>(main_namespace["res"]);
    } catch (py::error_already_set const &) {
        PyErr_Print();
    }
    BOOST_CHECK_EQUAL(res, 3);
}

BOOST_AUTO_TEST_CASE(game_test) {
    std::cout << "---GAME TEST---" << std::endl;
    Queues testQueues;
    std::shared_ptr<Queues> testQueuesHandler = std::make_shared<Queues>(testQueues);

    Config config;
    config.start = ConfigStart::CIRCLE;
    config.circle_is_bot = false;
    config.cross_is_bot = false;

    Model game(config, testQueuesHandler);
    testQueuesHandler->messageQueue.push(InputMessage(INPUT, 1, 1));
    testQueuesHandler->messageQueue.push(InputMessage(INPUT, 1, 0));
    testQueuesHandler->messageQueue.push(InputMessage(INPUT, 0, 0));
    testQueuesHandler->messageQueue.push(InputMessage(INPUT, 0, 2));
    testQueuesHandler->messageQueue.push(InputMessage(INPUT, 2, 2));
    testQueuesHandler->messageQueue.push(InputMessage(EXIT, 0, 0));
    game.start();
    auto tmp = testQueuesHandler->gameStateQueue.back();
    BOOST_CHECK_EQUAL(tmp.first, CIRCLE_WON);
}