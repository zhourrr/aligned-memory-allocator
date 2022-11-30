#ifndef ALIGNED_ALLOCATOR_H
#define ALIGNED_ALLOCATOR_H

#include <cstddef>
#include <memory>

// (zqr):
// A minimal implementation of an alloactor for C++ Standard Library, which
// allocates 512-byte aligned memory.
// Note:
//    A minimal custom allocator is preferred because C++ allocator_traits class
//    provides default implementation for you. Take a look at Microsoft's
//    documentation about Allocators and allocator class.
template <typename T> class AlignedAllocator {
public:
  typedef T value_type;

public:
  // According to Microsoft's documentation, default ctor is not required
  // by C++ Standard Library, because there is a default construct()
  AlignedAllocator() noexcept {};

  template <typename U>
  AlignedAllocator(const AlignedAllocator<U> &other) noexcept {};

  template <typename U>
  inline bool operator==(const AlignedAllocator<U> &other) const noexcept {
    return (this == &other);
  }

  template <typename U>
  inline bool operator!=(const AlignedAllocator<U> &other) const noexcept {
    return (this != &other);
  }

  inline value_type *allocate(const std::size_t n) const {
    value_type *ptr;
    // 512-byte aligned
    auto ret = posix_memalign((void **)&ptr, 512, n);
    if (ret != 0)
      throw std::bad_alloc();
    return ptr;
  };

  inline void deallocate(value_type *const ptr, std::size_t) const noexcept {
    free(ptr);
  }
};

#endif
