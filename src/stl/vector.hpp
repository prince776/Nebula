#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <utility>

#include "allocator/allocator.hpp"
#include "iterator.hpp"
#include "uniquePtr.hpp"

template <typename T, Allocator Alloc = Mallocator> class Vector {
  public:
    // Constructors
    Vector(Alloc allocator = {}) : allocator(allocator) {}
    Vector(size_t size, Alloc allocator = {})
        : m_size(size), capacity(size), allocator(allocator) {
        allocator = Alloc{};
        data = makeUnique<T[]>(allocator, capacity);
        fill(T{});
    }
    Vector(size_t size, const T& val, Alloc allocator = {})
        : m_size(size), capacity(size), allocator(allocator) {
        data = makeUnique<T[]>(capacity);
        fill(val);
    }
    Vector(std::initializer_list<T> ini, Alloc allocator = {})
        : m_size(ini.size()), capacity(ini.size()), allocator(allocator) {
        data = makeUnique<T[]>(capacity);
        auto it = begin();
        for (const auto& val : ini) {
            *it = val;
            it++;
        }
    }

    void resize(size_t newSize) {
        auto newCapacity = capacity;
        if (newSize > capacity) {
            newCapacity = capacity * 2 + 1;
        }
        realloc(newSize, newCapacity);
    }

    void push_back(const T& val) {
        if (capacity == m_size) {
            realloc(m_size, capacity * 2 + 1);
        }
        data[m_size++] = val;
    }
    void push_back(T&& val) {
        if (capacity == m_size) {
            realloc(m_size, m_size * 2 + 1);
        }
        data[m_size++] = std::move(val);
    }

    void pop_back() noexcept {
        assert(m_size > 0);
        m_size--;
    }

    T& front() { return data[0]; }
    T& back() { return data[m_size - 1]; }

    // Iterators
    ForwardIterator<T> begin() noexcept { return ForwardIterator(&data[0]); }
    ForwardIterator<T> end() noexcept {
        return ForwardIterator(&data[0] + m_size);
    }

    // Random access
    T& operator[](size_t idx) noexcept { return data[idx]; }
    const T& operator[](size_t idx) const noexcept { return data[idx]; }
    T& at(size_t idx) const noexcept {
        assert(idx >= m_size);
        return (*this)[idx];
    }

  private:
    void fill(const T& val) {
        for (size_t i = 0; i < m_size; i++) {
            data[i] = val;
        }
    }

    void realloc(size_t newSize, size_t newCapacity) {
        assert(newSize <= newCapacity);

        UniquePtr<T[]> newData = makeUnique<T[]>(newCapacity);
        size_t minSize = std::min(m_size, newSize);
        for (size_t i = 0; i < minSize; i++) {
            newData[i] = std::move(data[i]);
        }
        for (size_t i = minSize; i < newSize; i++) {
            newData[i] = T{};
        }
        auto newDataPtr = newData.release();
        data.reset(newDataPtr);
        m_size = newSize;
        capacity = newCapacity;
    }

  private:
    UniquePtr<T[]> data;
    Alloc allocator;
    size_t m_size = 0, capacity = 0;
};
