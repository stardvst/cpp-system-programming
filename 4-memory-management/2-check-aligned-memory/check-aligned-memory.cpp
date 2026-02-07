#include <iostream>
#include <type_traits>

using intAligned8 = std::aligned_storage<sizeof(int), 8>::type;
using intAligned4 = std::aligned_storage<sizeof(int), 4>::type;

int main()
{
	intAligned8 i; new (&i) int();
	intAligned4 j; new (&j) int();

	int *iu = &reinterpret_cast<int &>(i);
	*iu = 42;
	std::cout << "i: " << *iu << " or " << reinterpret_cast<int &>(i) << std::endl;

  int *ju = &reinterpret_cast<int &>(j);
  *ju = 24;
  std::cout << "j: " << *ju << " or " << reinterpret_cast<int &>(j) << std::endl;

	if (reinterpret_cast<unsigned long>(iu) % 8 == 0)
		std::cout << "i is 8-byte aligned" << std::endl;
	else
		std::cout << "i is not 8-byte aligned" << std::endl;

	if (reinterpret_cast<unsigned long>(ju) % 8 == 0)
		std::cout << "j is 8-byte aligned" << std::endl;
	else
		std::cout << "j is not 8-byte aligned" << std::endl;

	return 0;
}
