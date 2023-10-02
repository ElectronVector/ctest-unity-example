#include <stdio.h>
#include <stdbool.h>
#include "module_1.h"
#include "unity.h"
#include "fff.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_module_does_something() {
    int actual = multiply(3, 3);
    TEST_ASSERT_EQUAL_INT(9, actual);
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