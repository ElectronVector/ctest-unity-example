#include <stdio.h>
#include <stdbool.h>
#include "module_1.h"
#include "unity.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_module_does_something() {
    TEST_ASSERT(true);
}

void test_module_does_something_else() {
    TEST_ASSERT(true);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_module_does_something);
    RUN_TEST(test_module_does_something_else);
    return UNITY_END();
}