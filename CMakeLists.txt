cmake_minimum_required(VERSION 3.22)
project(c_example C)

set(CMAKE_C_STANDARD 11)

add_executable(c_example src/main.c
        src/module_1.c)

enable_testing()

set(TEST_DIRECTORY test)
set(TEST_FILE_PREFIX test_)
set(SOURCE_DIRECTORY src)
set(INCLUDE_DIRECTORY src)

# Collect a list of all the test files in the test directory.
file(GLOB TEST_FILES ${TEST_DIRECTORY}/${TEST_FILE_PREFIX}*)

# Add a new executable and test for each test file discovered.
# TODO: Add some actual functions to test in example modules.
# TODO: Compile with corresponding source files.
# TODO: Handle nested folders.
# TODO: Include unity for testing.
# TODO: Skip source files that don't exist.
foreach (TEST_FILE ${TEST_FILES})
    MESSAGE("Discovered test file: ${TEST_FILE}")
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WLE)

    # Remove the test filename prefix to get the module name.
    string(REGEX REPLACE ^${TEST_FILE_PREFIX} "" MODULE_NAME ${TEST_NAME})

    # Create a new binary and test for each module and corresponding test.
    add_executable(${TEST_NAME} ${TEST_FILE} ${SOURCE_DIRECTORY}/${MODULE_NAME}.c)
    target_include_directories(${TEST_NAME} PRIVATE ${INCLUDE_DIRECTORY})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach ()