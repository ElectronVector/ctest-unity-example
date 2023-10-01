cmake_minimum_required(VERSION 3.22)
project(c_example C)

set(CMAKE_C_STANDARD 11)

add_executable(c_example src/main.c
        src/module_1.c)

# Download and make the Unit test framework available.
include(FetchContent)
FetchContent_Declare(
        unity
        GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity
        GIT_TAG        v2.5.2
)
FetchContent_MakeAvailable(unity)

enable_testing()

set(TEST_DIRECTORY test)
set(TEST_FILE_PREFIX test_)
set(SOURCE_DIRECTORY src)
set(INCLUDE_DIRECTORY src)

# Collect a list of all the test files in the test directory.
file(GLOB TEST_FILES ${TEST_DIRECTORY}/${TEST_FILE_PREFIX}*)

# Add a new executable and test for each test file discovered.
# TODO: Handle nested folders.
# TODO: Include unity for testing.
# TODO: Skip source files that don't exist.
foreach (TEST_FILE ${TEST_FILES})
    message("Discovered test file: ${TEST_FILE}")
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WLE)

    # Remove the test filename prefix to get the module name.
    string(REGEX REPLACE ^${TEST_FILE_PREFIX} "" MODULE_NAME ${TEST_NAME})

    # Create a new binary and test for each module and corresponding test.
    add_executable(${TEST_NAME} ${TEST_FILE} ${SOURCE_DIRECTORY}/${MODULE_NAME}.c)
    # Include files from the include directory.
    target_include_directories(${TEST_NAME} PRIVATE ${INCLUDE_DIRECTORY})
    # Link in the Unity library.
    target_link_libraries(${TEST_NAME} unity)
    # Include the Unity headers.
    target_include_directories(${TEST_NAME} PRIVATE ${unity_SOURCE_DIR}/src)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach ()