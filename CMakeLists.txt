cmake_minimum_required(VERSION 3.17)
project(ZPR_gldg)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Boost 1.72.0 REQUIRED COMPONENTS python38)
find_package(Python 3.8 REQUIRED)
find_package(PythonLibs 3.8 REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
set(CMAKE_SHARED_MODULE_PREFIX "")

add_executable(hello src/main.cpp)

target_include_directories(hello PRIVATE ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})

target_link_libraries(hello Qt5::Widgets Boost::python38 ${PYTHON_LIBRARIES})