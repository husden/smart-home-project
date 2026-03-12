cmake_minimum_required(VERSION 3.23)
project(smart-home-project VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

add_executable(smart_home
        src/main.cpp
        include/devices/device.hpp
        include/sensors/sensor.hpp
        tests/devices/test_device.hpp
        tests/sensors/test_sensor.hpp
        tests/run_tests.cpp
)

enable_testing()

add_executable(run_tests
        tests/run_tests.cpp
        include/devices/light.hpp
        src/devices/light.cpp
        include/devices/thermostat.hpp
)

target_link_libraries(run_tests
        gtest_main
        pthread
)

include(GoogleTest)
gtest_discover_tests(run_tests)

