#pragma once
#include <array>
#include <stdlib.h>

#include <concepts>
#include <sys/_types/_uintptr_t.h>

struct Blk {
    void* ptr{nullptr};
    size_t size{0};
};

// wow my clangd formatting is messed up for concepts.

/**
 * @brief Based on cppcon talk from Andrei Alexandrescu
 * Ref: https://www.youtube.com/watch?v=LIb3L4vKZ7U
 */
template <typename Alloc>
concept Allocator = requires(Alloc alloc, size_t size) {
                        { alloc.allocate(size) } -> std::same_as<Blk>;
                        { alloc.deallocate(Blk{nullptr, size}) };
                        {
                            alloc.owns(Blk{nullptr, size})
                            } -> std::same_as<bool>;
                    };

template <Allocator alloc> class AllocatorTester {};
class MockAllocator {
  public:
    Blk allocate(size_t) { return Blk{}; }
    void deallocate(const Blk& blk) {}
    bool owns(const Blk& blk) { return false; }
};

template <Allocator P, Allocator F> class FallbackAllocator {
  public:
    FallbackAllocator(const P& primary, const F& fallback)
        : primaryAlloc(primary), fallbackAlloc(fallback) {}

    Blk allocate(size_t size) {
        auto blk = primaryAlloc.allocate(size);
        if (blk.ptr == nullptr) {
            blk = fallbackAlloc.allocate(size);
        }
        return blk;
    }

    void deallocate(const Blk& blk) {
        if (primaryAlloc.owns(blk)) {
            primaryAlloc.deallocate(blk);
        } else {
            fallbackAlloc.deallocate(blk);
        }
    }

    bool owns(const Blk& blk) {
        return primaryAlloc.owns(blk) || fallbackAlloc.owns(blk);
    }

  private:
    P primaryAlloc;
    F fallbackAlloc;
};

// Unaligned allocator for now.
using FallbackAllocatorTest =
    AllocatorTester<FallbackAllocator<MockAllocator, MockAllocator>>;

template <size_t MaxSize> class StackAllocator {
  public:
    StackAllocator() = default;

    Blk allocate(size_t size) {
        if (ptr + size > MaxSize) {
            return Blk{};
        }
        Blk res = {
            (void*)&buffer[ptr],
            size,
        };
        ptr += size;
        return res;
    }

    void deallocate(const Blk& blk) {
        if ((uintptr_t)blk.ptr + blk.size == (uintptr_t)&buffer[0] + ptr) {
            ptr -= blk.size;
        }
    }

    bool owns(const Blk& blk) {
        uintptr_t addrStart = &buffer[0];
        if ((uintptr_t)blk.ptr >= addrStart &&
            (uintptr_t)blk.ptr < addrStart + MaxSize) {
            return true;
        }
        return false;
    }

  private:
    int ptr{};
    std::array<uint8_t, MaxSize> buffer;
};

using StackAllocatorTest = AllocatorTester<StackAllocator<0>>;

class Mallocator {
  public:
    Mallocator() = default;

    Blk allocate(size_t size) { return Blk{malloc(size), size}; }
    void deallocate(const Blk& blk) {
        if (blk.ptr) {
            free(blk.ptr);
        }
    }
    bool owns(const Blk& blk) { return blk.ptr != nullptr; }
};

using MallocatorTest = AllocatorTester<Mallocator>;
