cmake_minimum_required(VERSION 3.20)
project(SmartHome VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(smarthome ${SOURCES})

if(MSVC)
    target_compile_options(smarthome PRIVATE /W4)
else()
    target_compile_options(smarthome PRIVATE -Wall -Wextra -Wpedantic)
endif()