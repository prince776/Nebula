#include <iostream>

#include "stl/vector.hpp"

inline int vector_test() {
    Vector<int> a(5, 10);
    std::cout << "Iterating: ";
    for (auto& x : a) {
        std::cout << x << ", ";
        x++;
    }
    std::cout << "\n";
    for (auto x : a) {
        std::cout << x << ", ";
    }
    std::cout << "\n";
    a[2] = 4;
    std::cout << a[2] << "\n";

    Vector<int> b = {1, 2, 3, 4};
    for (auto x : b) {
        std::cout << x << " | ";
    }
    std::cout << "\n";
    b.push_back(5);
    b.push_back(77);
    for (auto x : b) {
        std::cout << x << " | ";
    }
    std::cout << "\n";

    b.resize(10);
    for (auto x : b) {
        std::cout << x << " | ";
    }
    std::cout << "\n";
    b.resize(3);
    for (auto x : b) {
        std::cout << x << " | ";
    }
    std::cout << "\n";
    return 0;
}
