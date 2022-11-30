# aligned allocator for C++ STL containers

A custom allocator, which allocates 512-byte aligned memory, for C++ Standard Library to handle the allocation and deallocation of elements stored in containers. (tested with C++ 17)

In another project, I was given a std::string as a buffer, and I had to use Linux O_DIRECT write to bypass the Linux kernel's caches. O_DIRECT requries 512-byte alignment. I ended up making this allocator to conform to the requirement. 

See test.cpp for example use.