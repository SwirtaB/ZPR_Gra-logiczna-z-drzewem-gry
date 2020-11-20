//
// Created by swirta on 20.11.2020.
//

#define BOOST_TEST_MODULE ClassTests

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

BOOST_AUTO_TEST_CASE(basicTest1)
{
    std::cout << "---TEST---" << std::endl;
    int i = 2;
    i += i;
    BOOST_CHECK_EQUAL(i, 4);
}


