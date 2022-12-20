#include <bits/stdc++.h>

#include "stl/uniquePtr.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);
    {
        UniquePtr<int> ptr2 = makeUnique<int>(123);
        std::cout << "Val: " << *ptr2 << std::endl;
    }
    std::cout << "Test\n";
}
