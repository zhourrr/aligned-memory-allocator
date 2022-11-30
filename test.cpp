#include "aligned_allocator.h"
#include <iostream>
#include <string>

int main() {
  using std::cout;
  using std::endl;
  using my_string =
      std::basic_string<char, std::char_traits<char>, AlignedAllocator<char>>;

  // The buffer is a C++ string with a 512-byte aligned data buffer.
  // The alignment is required by O_DIRECT.
  // Note that std::string is a type alias for
  //    std::basic_string<char, std::char_traits<char>, std::allocator<char>>
  my_string buf{};

  // Note that since in the initialization step no argument was given, the buf
  // is empty and the custom allocate function was not called, the current
  // buffer is not aligned.
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

  std::string filename = "output";
  // int ret = posix_memalign((void **)&direct, 512, file_size);
  // for (int i = 0; i < file_size; ++i)
  //   direct[i] = 't';

  // int fd = ::open(filename.c_str(), O_RDWR | O_APPEND | O_CREAT, 0644);
  // // auto start = std::chrono::high_resolution_clock::now();
  // for (int i = 0; i < 1; ++i) {
  //   ssize_t write_result = ::write(fd, direct, file_size);
  //   if (write_result < 0) {
  //     std::cout << "error: " << errno << std::endl;
  //   }
  // }
  // close(fd);

  // // read
  // fd = ::open(filename.c_str(), O_RDONLY | O_DIRECT);
  // char *buf;
  // ret = posix_memalign((void **)&buf, 512, file_size);
  // ssize_t read_size = ::pread(fd, buf, 1024, file_size - 512);
  // if (read_size <= 0)
  //   std::cout << "Read error" << std::endl;
  // else
  //   std::cout << "successfully read " << read_size << " bytes" << std::endl;

  // auto end = std::chrono::high_resolution_clock::now();
  // auto duration =
  //     std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  // std::cout << "cached duration: " << duration.count() << std::endl;
  // close(fd);

  // filename = "direct";
  // fd = ::open(filename.c_str(), O_RDWR | O_APPEND | O_CREAT | O_DIRECT,
  // 0644); start = std::chrono::high_resolution_clock::now(); for (int i = 0; i
  // < rounds; ++i) {
  //   ssize_t write_result = ::write(fd, direct, file_size);
  //   if (write_result < 0) {
  //     std::cout << "error: " << errno << std::endl;
  //   }
  // }
  // end = std::chrono::high_resolution_clock::now();
  // duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
  // std::cout << "direct duration: " << duration.count() << std::endl;
}