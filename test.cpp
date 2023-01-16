#include "aligned_allocator.h"
#include <cstdint>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

int main() {
    using std::cout;
    using std::endl;

    // my_string is a C++ string with a 512-byte aligned char buffer.
    // O_DIRECT requires 512-byte alignment.
    // Note that std::string is a type alias for
    //    std::basic_string<char, std::char_traits<char>, std::allocator<char>>
    using my_string = std::basic_string<char, std::char_traits<char>, AlignedAllocator<char, 512>>;
    my_string buf{};

    // Note that since in the initialization step no argument was given, the buf
    // is empty and the custom allocate function was not called, the current
    // buffer is not aligned (search for Short String Optimization for details).
    cout << "Buffer address:" << (uint64_t)buf.data()
         << ", address % 512 = " << (uint64_t)buf.data() % 512 << endl;

    // Clear the buffer and reserve some space. Now the buffer is aligned because
    // the custom allocate function was called for the allocation.
    buf.clear();
    buf.reserve(100);
    cout << "Buffer address: " << (uint64_t)buf.data()
         << ", address % 512 = " << (uint64_t)buf.data() % 512 << endl;

    // From now on, the buffer address will always be aligned to 512 bytes.
    uint64_t length = 128 * 1024 * 1024;
    buf.append(length, 'z');
    cout << "Buffer address: " << (uint64_t)buf.data()
         << ", address % 512 = " << (uint64_t)buf.data() % 512 << endl;

    // Test direct I/O
    auto filename = "output";
    auto fd = ::open(filename, O_RDWR | O_CREAT | O_DIRECT);
    auto write_size = ::write(fd, buf.data(), buf.size());
    if (write_size < 0) {
        cout << "error: " << errno << endl;
    } else {
        cout << "Successfully written " << write_size << " bytes." << endl;
    }
    close(fd);

    // also works with std::vector
    std::vector<uint32_t, AlignedAllocator<uint32_t, 512>> my_vec{};
    my_vec.resize(50);
    cout << "Buffer address: " << (uint64_t)my_vec.data()
         << ", address % 512 = " << (uint64_t)my_vec.data() % 512 << endl;

    for (int i = 0; i < 1024 * 1024 * 2; ++i)
        my_vec.push_back(i);
    cout << "Buffer address: " << (uint64_t)my_vec.data()
         << ", address % 512 = " << (uint64_t)my_vec.data() % 512 << endl;
}
