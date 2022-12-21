#include <bits/stdc++.h>

#include <memory>

#include "stl/uniquePtr.hpp"

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
}
