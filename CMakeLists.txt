cmake_minimum_required(VERSION 3.22)
project(c_example C)

set(CMAKE_C_STANDARD 11)

include(CMakePrintHelpers)

add_executable(c_example src/main.c
        src/module_1.c src/module_2.c src/module_folder/module.c src/module_folder/module.h)

# Download and make the Unit test framework available.
include(FetchContent)
FetchContent_Declare(
        unity
        GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity
        GIT_TAG        v2.5.2
)
FetchContent_MakeAvailable(unity)

FetchContent_Declare(
        fff
        GIT_REPOSITORY https://github.com/meekrosoft/fff
        GIT_TAG        v1.1
)
FetchContent_MakeAvailable(fff)

enable_testing()

set(TEST_DIRECTORY test)
set(TEST_FILE_PREFIX test_)
set(SOURCE_DIRECTORY src)
set(INCLUDE_DIRECTORY src)

cmake_print_variables(INCLUDE_DIRECTORY)
cmake_print_variables(SOURCE_DIRECTORY)
cmake_print_variables(TEST_DIRECTORY)
cmake_print_variables(TEST_FILE_PREFIX)

# Collect a list of all the test files in the test directory.
set(ABSOLUTE_TEST_DIRECTORY_PATH ${CMAKE_SOURCE_DIR}/${TEST_DIRECTORY})
file(GLOB_RECURSE TEST_FILES RELATIVE ${ABSOLUTE_TEST_DIRECTORY_PATH} ${TEST_DIRECTORY}/${TEST_FILE_PREFIX}*)

# Log the test files that were found.
message("")
message ("Discovered test files")
foreach(f ${TEST_FILES})
    message("    " ${f})
endforeach ()
message("")

# Add a new executable and test for each test file discovered.
# TODO: Skip source files that don't exist.
foreach (TEST_FILE ${TEST_FILES})

    # Remove the test filename prefix to get the path to the corresponding source file.
    string(REGEX REPLACE ${TEST_FILE_PREFIX} "" SOURCE_FILE_PATH ${TEST_FILE})
    cmake_path(REMOVE_EXTENSION SOURCE_FILE_PATH OUTPUT_VARIABLE MODULE_PATH)
    string(REGEX REPLACE "/" "-" TEST_NAME ${MODULE_PATH})

    # Create a new binary and test for each module and corresponding test.
    add_executable(${TEST_NAME} test/${TEST_FILE} src/${SOURCE_FILE_PATH})
    # Include files from the include directory.
    target_include_directories(${TEST_NAME} PRIVATE ${INCLUDE_DIRECTORY})
    # Link in the Unity library.
    target_link_libraries(${TEST_NAME} unity)
    # Include the Unity and fff headers.
    target_include_directories(${TEST_NAME} PRIVATE ${unity_SOURCE_DIR}/src)
    target_include_directories(${TEST_NAME} PRIVATE ${fff_SOURCE_DIR})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach ()