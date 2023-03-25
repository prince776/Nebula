#include <iostream>

#include "stl/string.hpp"
#include "tests/common.hpp"

inline int string_test() {
    String s(5, 'a');
    for (int i = 0; i < 5; i++) {
        ASSERT(s[i] == 'a')
    }
    String s2("Test");
    ASSERT(s2[0] == 'T')
    ASSERT(s2[1] == 'e')
    ASSERT(s2[2] == 's')
    ASSERT(s2[3] == 't')

    String s3 = s2;
    ASSERT(s3 == s2);

    return 0;
}
