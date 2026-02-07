#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define FILEPATH "mmapped.txt"
#define NUM_OF_ITEMS_IN_FILE (1000)
#define FILESIZE (NUM_OF_ITEMS_IN_FILE * sizeof(int))

int main()
{
	int fd = open(FILEPATH, O_RDONLY);
	if (fd == -1)
	{
		std::cerr << "Failed to open file" << std::endl;
		return 1;
	}

	int *map = (int *)mmap(0, FILESIZE, PROT_READ, MAP_SHARED, fd, 0);
	if (map == MAP_FAILED)
	{
		std::cerr << "Failed to map file to memory" << std::endl;
		close(fd);
		return 2;
	}

	for (int i = 0; i < NUM_OF_ITEMS_IN_FILE; i++)
		std::cout << "map[" << i << "] = " << map[i] << std::endl;

	if (munmap(map, FILESIZE) == -1)
	{
		std::cerr << "Failed to unmap memory" << std::endl;
		close(fd);
		return 3;
	}

	close(fd);

	return EXIT_SUCCESS;
}
