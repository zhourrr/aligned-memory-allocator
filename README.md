# Aligned Allocator for C++ STL Containers

A custom allocator, which allocates aligned memory, for C++ Standard Library to handle the allocation and reclamation of elements stored in containers. (tested with C++17)

In another project, I was given a `std::string` as a buffer, and I had to use Linux `O_DIRECT` write to bypass the Linux kernel's caches. `O_DIRECT` requires 512-byte alignment. I ended up making this allocator to conform to the requirement. The aligned_allocator is defined in the **aligned_allocator.h** file.

See test.cpp for explanation and typical usage.

Create a string which holds 512-byte aligned buffer.

```cpp
  using aligned_str = std::basic_string<char, std::char_traits<char>, AlignedAllocator<char, 512>>;
  aligned_str buf{};
  buf.reserve(10);
  
  buf.append(1024, 'z');
  // print the buffer address
  std::cout << "Buffer address: " << (uint64_t)buf.data() << ", address % 512 = " << (uint64_t)buf.data() % 512 << std::endl;
    ...
```
