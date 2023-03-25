#include <_types/_uint64_t.h>
#include <_types/_uint8_t.h>
#include <iostream>

#include "stl/bitset.hpp"
#include "tests/common.hpp"

inline int bitset_test() {
    Bitset<> a(10);

    auto bit = a[1];
    ASSERT(bit == 0)
    bit = 1;
    ASSERT(bit == 1);

    std::cout << "bitset: ";
    for (int i = 0; i < 10; i++) {
        if (i % 3 == 0) {
            a[i] = 1;
            ASSERT(a[i] == 1)
        }
        std::cout << a[i] << ", ";
    }
    return 0;
}
