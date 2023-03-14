#include "allocator-test.hpp"
#include "uniquePtr-test.hpp"
#include "vector-test.hpp"

#define RUN_TEST(x)                                                            \
    try {                                                                      \
        if (x())                                                               \
            return 1;                                                          \
    } catch (...) {                                                            \
        return 1;                                                              \
    }

int main() {
    RUN_TEST(vector_test)
    RUN_TEST(uniquePtr_test)
    RUN_TEST(allocator_test)
    return 0;
}
