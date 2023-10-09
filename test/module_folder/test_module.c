#include "unity.h"

#include "module_folder/module.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_to_do() {
    TEST_ASSERT_EQUAL_INT(5, a_function());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_to_do);
    return UNITY_END();
}