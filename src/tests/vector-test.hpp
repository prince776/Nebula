#include <iostream>

#include "stl/vector.hpp"
#include "tests/common.hpp"

inline int vector_test() {
    Vector<int> a(5, 10);
    std::cout << "Iterating: ";
    for (auto& x : a) {
        std::cout << x << ", ";
        if (x != 10)
            FAIL_TEST
        x++;
    }
    std::cout << "\n";
    for (auto x : a) {
        if (x != 11)
            FAIL_TEST
        std::cout << x << ", ";
    }
    std::cout << "\n";
    a[2] = 4;
    std::cout << a[2] << "\n";
    if (a[2] != 4)
        FAIL_TEST

    Vector<int> b = {1, 2, 3, 4};
    for (auto x : b) {
        std::cout << x << " | ";
    }
    for (int i = 0; i < 4; i++) {
        if (b[i] != i + 1)
            FAIL_TEST
    }
    std::cout << "\n";
    b.push_back(5);
    b.push_back(77);
    if (b[4] != 5)
        FAIL_TEST
    if (b[5] != 77)
        FAIL_TEST
    for (auto x : b) {
        std::cout << x << " | ";
    }
    std::cout << "\n";

    b.resize(10);
    for (int i = 6; i < 10; i++) {
        if (b[i] != 0)
            FAIL_TEST;
    }
    for (auto x : b) {
        std::cout << x << " | ";
    }
    std::cout << "\n";
    b.resize(3);
    for (int i = 0; i < 3; i++) {
        if (b[i] != i + 1)
            FAIL_TEST;
    }
    for (auto x : b) {
        std::cout << x << " | ";
    }
    std::cout << "\n";

    Vector<int> c = a;
    for (int i = 0; i < c.size(); i++) {
        ASSERT(c[i] == a[i]);
    }

    c = b;
    for (int i = 0; i < c.size(); i++) {
        ASSERT(c[i] == b[i]);
    }

    return 0;
}
