#ifndef ALIGNED_ALLOCATOR_H
#define ALIGNED_ALLOCATOR_H

#include <memory>
#include <stdlib.h>

// (zqr):
// A minimal implementation of an alloactor for C++ Standard Library, which
// allocates aligned memory (specified by the alignment argument).
// Note:
//    A minimal custom allocator is preferred because C++ allocator_traits class
//    provides default implementation for you. Take a look at Microsoft's
//    documentation about Allocators and allocator class.
template <typename T, std::size_t alignment> class AlignedAllocator {
public:
  using value_type = T;

public:
  // According to Microsoft's documentation, default ctor is not required
  // by C++ Standard Library.
  AlignedAllocator() noexcept {};

  template <typename U>
  AlignedAllocator(const AlignedAllocator<U, alignment> &other) noexcept {};

  template <typename U>
  inline bool
  operator==(const AlignedAllocator<U, alignment> &other) const noexcept {
    return true;
  }

  template <typename U>
  inline bool
  operator!=(const AlignedAllocator<U, alignment> &other) const noexcept {
    return false;
  }

  template <typename U> struct rebind {
    using other = AlignedAllocator<U, alignment>;
  };

  inline value_type *allocate(const std::size_t n) const {
    auto size = n;
    /*
      if you wish the allocated buffer size to also be aligned to alignment,
      uncomment the following statement
    */
    // size = (n + alignment - 1) / alignment * alignment;
    value_type *ptr;
    auto ret = posix_memalign((void **)&ptr, alignment, sizeof(T) * size);
    if (ret != 0)
      throw std::bad_alloc();
    return ptr;
  };

  inline value_type *allocate(const std::size_t n, const void *hint) {
    return allocate(n);
  }

  inline void deallocate(value_type *const ptr, std::size_t n) const noexcept {
    free(ptr);
  }
};

#endif
