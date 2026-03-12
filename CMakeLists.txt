cmake_minimum_required(VERSION 3.20)
project(SmartHome)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_PATH "/Users/tyagunova_daria/CLionProjects/smart-home-project")

# Все папки с заголовочными файлами
include_directories(
        ${PROJECT_PATH}/include
        ${PROJECT_PATH}/include/devices
        ${PROJECT_PATH}/include/sensors
        ${PROJECT_PATH}/include/rules
        ${PROJECT_PATH}/include/system
        ${PROJECT_PATH}/include/exceptions
)

file(GLOB_RECURSE SOURCES
        ${PROJECT_PATH}/src/*.cpp
)

add_executable(smarthome ${SOURCES})
