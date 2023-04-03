#pragma once

#include <cassert>
#include <vector>

class DSU {
  public:
    DSU() = default;
    explicit DSU(int n) : n(n), parentOrSize(n, -1) {}

    int parent(int a) {
        assert(0 <= a && a < n);
        if (parentOrSize[a] < 0) {
            return a;
        }
        return parentOrSize[a] = parent(parentOrSize[a]);
    }

    bool same(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        return parent(a) == parent(b);
    }

    int size(int a) {
        assert(0 <= a && a < n);
        return -parentOrSize[parent(a)];
    }

    int join(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);

        int pa = parent(a), pb = parent(b);
        if (pa == pb) {
            return pa;
        }
        if (-parentOrSize[pa] < -parentOrSize[pb]) {
            std::swap(pa, pb);
        }
        parentOrSize[pa] += parentOrSize[pb];
        parentOrSize[pb] = pa;
        return pa;
    }

  private:
    int n{};
    // If < 0, then it's the root and the component size is -1 * val
    // otherwise, tell's the parent.
    std::vector<int> parentOrSize{};
};
