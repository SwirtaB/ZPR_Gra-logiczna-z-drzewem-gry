cmake_minimum_required(VERSION 3.17)
project(ZPR_gldg)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Boost 1.71.0 REQUIRED COMPONENTS python38)
find_package(Python 3.8 REQUIRED)
find_package(PythonLibs 3.8 REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
set(CMAKE_SHARED_MODULE_PREFIX "")


file(GLOB TARGET_SRC "./src/*.cpp" )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS)

set(EXECUTABLE_NAME "hello")
add_executable(${EXECUTABLE_NAME} ${TARGET_SRC})

target_include_directories(${EXECUTABLE_NAME} PRIVATE ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})

target_link_libraries(${EXECUTABLE_NAME} Qt5::Widgets Boost::python38 ${PYTHON_LIBRARIES})

#Add tests -> building program for testing with boost
set(BUILD_TESTS True) #Set to "True" for test for building tests

if(BUILD_TESTS)
    message("Building tests.")
    list(FILTER TARGET_SRC EXCLUDE REGEX /*/main.cpp)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)

    add_executable(tests ${CMAKE_HOME_DIRECTORY}/tests/basicTest.cpp ${TARGET_SRC} tests/basicTest.cpp)
    target_link_libraries(tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

    add_test(UnitTest tests)
    enable_testing()
endif()