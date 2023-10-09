#include "unity.h"
#include "fff.h"

//#include "module_1.h"

//DEFINE_FFF_GLOBALS;
//FAKE_VALUE_FUNC(int, module_2_get_int);

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_to_do() {
    TEST_ASSERT_EQUAL_INT(9, 9);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_to_do);
    return UNITY_END();
}