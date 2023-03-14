#include "uniquePtr-test.hpp"
#include "vector-test.hpp"

#define RUN_TEST(x) \
    if (x()) return 1

int main() {
    // The test functions are defined in header file that can
    // lead to ODR violation, but only this file will include them so issoke.
    RUN_TEST(vector_test);
    RUN_TEST(uniquePtr_test);

    return 0;
}
