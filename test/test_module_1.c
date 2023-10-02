#include <stdio.h>
#include <stdbool.h>
#include "unity.h"
#include "fff.h"

#include "module_1.h"

DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC(int, module_2_get_int);

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
    module_2_get_int_fake.return_val = 1;
    int actual = call_module_2();
    TEST_ASSERT_EQUAL_INT(1, actual);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_module_does_something);
    RUN_TEST(test_module_does_something_else);
    return UNITY_END();
}