#include "allocator/allocator.hpp"
#include <iostream>
#include <utility>

template <Allocator Alloc, typename T> class ObjectFactory {
  public:
    template <typename... Args> ObjectFactory(Alloc& alloc, Args&&... args) {
        auto blk = alloc.allocate(sizeof(T));
        t = new (blk.ptr) T(std::forward<Args>(args)...);
    }

    T& get() { return *t; }

  private:
    T* t;
};

class Vec2 {
  public:
    Vec2() = default;
    Vec2(int x, int y) : x(x), y(y) {}
    int x, y;
};

inline int allocator_test() {
    auto mallocator = Mallocator{};
    auto vec2Factory = ObjectFactory<Mallocator, Vec2>(mallocator, 4, 5);
    std::cout << "Vec2 created at:" << &vec2Factory.get() << "\n";
    std::cout << "Vec2 values: " << vec2Factory.get().x << ","
              << vec2Factory.get().y << "\n";
    return 0;
}
