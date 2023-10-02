# CTest Example

This is a simple example of a C application which can build and run unit tests with CTest.

It uses [Unity](https://github.com/ThrowTheSwitch/Unity) as a test framework. 

## Conventions
This application has all of its source files in a folder called `src` and all test files in `test`.
These can be changed in `CMakeLists.txt`.

By convention, test a file named `src/module.c` by adding a test file called `test/test_module.c`.
This file will be built and linked against the source file to execute the tests.
The `test_` is the prefix for a test file name, but this prefix can be changed in `CMakeLists.txt`.

## Adding New Modules and Tests
Add a new module and test by creating three different files:
- `src/<module_name>.c`
- `src/<module_name>.h`
- `test/test_<module_name.c>`

The test file created should include 

## Running CMake

The modern way to build with CMake is to create a build dir with:
```
cmake -S . -B build
```

This tells CMake the source and build directories and then generates the build system.

Then instead of running the built makefiles (or Ninja files) directly, use CMake to run the build tool with the --build option:

```
cmake --build build
```

## Running Tests

After 1) the build system has been generated and 2) the build is run, the tests can be run with CTest.
```shell
ctest --test-dir build
```

The build folder must be supplied to CTest with the `--test-dir` argument so that CTest knows where to find the tests.

## Implementation Details

### Subdirectories

You could put a CMakeLists folder in the test folder and then include it with:
```
add_subdirectory(test)
```

When it is time to run the tests though, you need to run them by speficifing the build subdirectory:
```
ctest --test-dir build/test
```

## To Do
You can use gcc to determine module dependencies like this:
```
gcc -MM test\test_module_1.c -Isrc -Itest
test_module_1.o: test\test_module_1.c src/module.h
```
This could be useful for automatically detecting the files to include in the test executable.