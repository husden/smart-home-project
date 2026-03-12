cmake_minimum_required(VERSION 3.20)
project(SmartHome)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_PATH "/Users/tyagunova_daria/CLionProjects/smart-home-project")

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

    function(add_project_test TEST_NAME TEST_FILES)
        add_executable(${TEST_NAME} ${TEST_FILES})
        target_link_libraries(${TEST_NAME} ${GTEST_LIBRARIES} pthread)
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endfunction()

    file(GLOB_RECURSE TEST_SOURCES
            ${PROJECT_PATH}/tests/*.cpp
    )

    foreach(TEST_FILE ${TEST_SOURCES})
        get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
        add_project_test(${TEST_NAME} ${TEST_FILE})
        message(STATUS "✅ Test added: ${TEST_NAME}")
    endforeach()

    message(STATUS "🎯 Total test files: ${TEST_SOURCES}")
endif()