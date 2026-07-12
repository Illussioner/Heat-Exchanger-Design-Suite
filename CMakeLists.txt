cmake_minimum_required(VERSION 3.16)

project(HeatExchangerDesignSuite)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(
    HeatExchanger

    src/main.cpp
    src/Fluid.cpp
    src/HeatExchanger.cpp
)