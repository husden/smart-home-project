cmake_minimum_required(VERSION 3.20)
project(SmartHome)

set(CMAKE_CXX_STANDARD 23)

set(PROJECT_PATH ${CMAKE_SOURCE_DIR})

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

option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    enable_testing()

    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    add_executable(test_condition_rule
            ${PROJECT_PATH}/tests/rules/test_condition_rule.cpp
            ${PROJECT_PATH}/src/rules/condition_rule.cpp
            ${PROJECT_PATH}/src/sensors/motion_sensor.cpp
    )
    target_link_libraries(test_condition_rule ${GTEST_LIBRARIES} pthread)
    add_test(NAME test_condition_rule COMMAND test_condition_rule)

    add_executable(test_scheduled_rule
            ${PROJECT_PATH}/tests/rules/test_scheduled_rule.cpp
            ${PROJECT_PATH}/src/rules/scheduled_rule.cpp
    )
    target_link_libraries(test_scheduled_rule ${GTEST_LIBRARIES} pthread)
    add_test(NAME test_scheduled_rule COMMAND test_scheduled_rule)

    add_executable(test_smart_home
            ${PROJECT_PATH}/tests/system/test_smart_home.cpp
            ${PROJECT_PATH}/src/system/smart_home_system.cpp
            ${PROJECT_PATH}/src/devices/light.cpp
            ${PROJECT_PATH}/src/sensors/motion_sensor.cpp
            ${PROJECT_PATH}/src/rules/condition_rule.cpp
    )
    target_link_libraries(test_smart_home ${GTEST_LIBRARIES} pthread)
    add_test(NAME test_smart_home COMMAND test_smart_home)

    add_executable(test_command_processor
            ${PROJECT_PATH}/tests/system/test_command_processor.cpp
            ${PROJECT_PATH}/src/system/command_processor.cpp
    )
    target_link_libraries(test_command_processor ${GTEST_LIBRARIES} pthread)
    add_test(NAME test_command_processor COMMAND test_command_processor)

    message(STATUS "🎯 Tests configured")
endif()