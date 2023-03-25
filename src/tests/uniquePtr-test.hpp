#include <iostream>

#include "stl/uniquePtr.hpp"
#include "common.hpp"

inline int uniquePtr_test() {
    UniquePtr<int> p = makeUnique<int>(123);
    UniquePtr<int[]> p2 = makeUnique<int[]>(5);
    std::cout << "Val: " << *p << std::endl;
    if (*p != 123) {
        return 1;
    }
    p2[0] = 1;
    p2[1] = 2;
    std::cout << "Val2: " << p2[0] << ", " << p2[1] << std::endl;
    if (p2[0] != 1 || p2[1] != 2) {
        return 1;
    }
    return 0;
}
