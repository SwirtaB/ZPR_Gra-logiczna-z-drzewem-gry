cmake_minimum_required(VERSION 3.17)
project(ZPR_gldg)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(Boost_USE_STATIC_LIBS ON)

find_package(Qt5Widgets REQUIRED)
find_package(Boost REQUIRED)

add_executable(hello src/main.cpp)

target_include_directories(hello PUBLIC ${Boost_INCLUDE_DIRS})

target_link_libraries(hello Qt5::Widgets)