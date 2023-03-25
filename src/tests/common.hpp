#pragma once

#define FAIL_TEST                                                              \
    { return 1; }

#define ASSERT(x)                                                              \
    if (!(x)) {                                                                \
        return 1;                                                              \
    }
