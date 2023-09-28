cmake_minimum_required(VERSION 3.22)
project(c_example C)

set(CMAKE_C_STANDARD 11)

add_executable(c_example src/main.c
        src/test_suite_1.c)

enable_testing()

#add_executable(test_suite_1 test/test_suite_1.c)
#add_executable(test_suite_2 test/test_suite_2.c)
#
#add_test(NAME test_suite_1 COMMAND test_suite_1)
#add_test(NAME test_suite_2 COMMAND test_suite_2)

# Collect a list of all the test files in the test directory.
file(GLOB TEST_FILES test/test_*)

# Add a new executable and test for each test file discovered.
# TODO: Remove test_ prefix from test file to get source file name.
# TODO: Add some actual functions to test in example modules.
# TODO: Compile with corresponding source files.
# TODO: Handle nested folders.
# TODO: Include unity for testing.
# TODO: Skip source files that don't exist.
foreach (TEST_FILE ${TEST_FILES})
    MESSAGE("Discovered test file: ${TEST_FILE}")
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WLE)
    add_executable(${TEST_NAME} ${TEST_FILE} ../src/${TEST_NAME}.c)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach ()