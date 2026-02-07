#include <iostream>
#include <type_traits>

using intAligned = std::aligned_storage<sizeof(int), std::alignment_of<int>::value>::type;

int main()
{
	std::cout << "int alignment: " << std::alignment_of<int>::value << std::endl;
	std::cout << "double alignment: " << std::alignment_of<double>::value << std::endl;
	std::cout << "intAligned alignment: " << std::alignment_of<intAligned>::value << std::endl;

	intAligned i, j;
	new (&i) int();
	new (&j) int();

	int *iu = &reinterpret_cast<int &>(i);
	*iu = 42;
	std::cout << "i: " << *iu << " or " << reinterpret_cast<int &>(i) << std::endl;

  int *ju = &reinterpret_cast<int &>(j);
  *ju = 24;
  std::cout << "j: " << *ju << " or " << reinterpret_cast<int &>(j) << std::endl;

	return 0;
}
