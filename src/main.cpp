#include <bits/iterator_concepts.h>
#include <bits/stdc++.h>

#include <concepts>
#include <iterator>
#include <memory>

#include "stl/uniquePtr.hpp"
#include "stl/vector.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);
    {
        UniquePtr<int> p = makeUnique<int>(123);
        UniquePtr<int[]> p2 = makeUnique<int[]>(5);
        std::cout << "Val: " << *p << std::endl;
        p2[0] = 1;
        p2[1] = 2;
        std::cout << "Val2: " << p2[0] << ", " << p2[1] << std::endl;
    }

    {
        Vector<int> a(5, 10);
        std::cout << "Iterating: ";
        for (auto &x : a) {
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
    }
}
