cmake_minimum_required(VERSION 3.22)
project(ctest-unity-example C)

set(CMAKE_C_STANDARD 11)

include(CMakePrintHelpers)

set(TEST_DIRECTORY test)
set(TEST_FILE_PREFIX test_)
set(SOURCE_DIRECTORY src)
set(INCLUDE_DIRECTORY src)

cmake_print_variables(INCLUDE_DIRECTORY)
cmake_print_variables(SOURCE_DIRECTORY)
cmake_print_variables(TEST_DIRECTORY)
cmake_print_variables(TEST_FILE_PREFIX)

# Collect a list of all the source files in the source directory.
set(ABSOLUTE_SOURCE_DIRECTORY_PATH ${CMAKE_SOURCE_DIR}/${SOURCE_DIRECTORY})
file(GLOB_RECURSE SOURCE_FILES ${SOURCE_DIRECTORY}/*)
add_executable(ctest-unity-example ${SOURCE_FILES})

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

# Collect a list of all the test files in the test directory.
set(ABSOLUTE_TEST_DIRECTORY_PATH ${CMAKE_SOURCE_DIR}/${TEST_DIRECTORY})
file(GLOB_RECURSE TEST_FILES RELATIVE ${ABSOLUTE_TEST_DIRECTORY_PATH} ${TEST_DIRECTORY}/${TEST_FILE_PREFIX}*)

# Log the test files that were found.
message (STATUS "Discovered test files")
foreach(f ${TEST_FILES})
    message(STATUS "    " ${f})
endforeach ()

# Add a new executable and test for each test file discovered.
foreach (TEST_FILE ${TEST_FILES})

    # Remove the test filename prefix to get the path to the corresponding source file.
    string(REGEX REPLACE ${TEST_FILE_PREFIX} "" SOURCE_FILE ${TEST_FILE})
    cmake_path(REMOVE_EXTENSION SOURCE_FILE OUTPUT_VARIABLE MODULE_PATH)

    # Convert slashes to hyphens to generate a unique name for the test.
    string(REGEX REPLACE "/" "-" MODULE_TEST_NAME ${MODULE_PATH})

    # Create a new executable binary for each module test. Don't add the source file if it doesn't exist.
    set(SOURCE_FILE_IF_IT_EXISTS "")
    if(EXISTS ${PROJECT_SOURCE_DIR}/src/${SOURCE_FILE})
        set(SOURCE_FILE_IF_IT_EXISTS src/${SOURCE_FILE})
    endif()
    add_executable(${MODULE_TEST_NAME} test/${TEST_FILE} ${SOURCE_FILE_IF_IT_EXISTS})

    # Include files from the include directory.
    target_include_directories(${MODULE_TEST_NAME} PRIVATE ${INCLUDE_DIRECTORY})

    # Link in the Unity library.
    target_link_libraries(${MODULE_TEST_NAME} unity)

    # Include the Unity and fff headers.
    target_include_directories(${MODULE_TEST_NAME} PRIVATE ${unity_SOURCE_DIR}/src)
    target_include_directories(${MODULE_TEST_NAME} PRIVATE ${fff_SOURCE_DIR})

    # Add the test so it can be run with CTest.
    add_test(NAME ${MODULE_TEST_NAME} COMMAND ${MODULE_TEST_NAME})
    message(STATUS "Added test: " ${MODULE_TEST_NAME})
endforeach ()