#include "module_1.h"
#include "module_2.h"

int multiply (int a, int b) {
    return a*b;
}

int call_module_2() {
    return module_2_get_int();
}
