#include <cstring>
#include <iostream>
#include <sys/mman.h>

constexpr auto SIZE = 1024;

int main()
{
	auto *addr = static_cast<char *>(mmap(nullptr, SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0));
	if (addr == MAP_FAILED)
	{
		std::cerr << "Failed to allocate memory using mmap" << std::endl;
		return 1;
	}

	std::cout << "Memory allocated at address: " << addr << std::endl;

	strcpy(addr, "Hello, mmap!");
	std::cout << "Data written to memory: " << addr << std::endl;

  if (munmap(addr, SIZE) == -1)
  {
    std::cerr << "Failed to unmap memory" << std::endl;
    return 2;
  }

	return 0;
}
