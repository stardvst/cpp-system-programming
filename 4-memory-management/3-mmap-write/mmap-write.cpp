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
	int fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
	if (fd == -1)
	{
		std::cerr << "Failed to open file" << std::endl;
		return 1;
	}

	int result = lseek(fd, FILESIZE - 1, SEEK_SET);
	if (result == -1)
	{
		std::cerr << "Failed to stretch the file" << std::endl;
		close(fd);
		return 2;
	}

	result = write(fd, "", 1);
	if (result != 1)
	{
		std::cerr << "Failed to write last byte of the file" << std::endl;
		close(fd);
		return 3;
	}

	int *map = (int *)mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (map == MAP_FAILED)
	{
		std::cerr << "Failed to map file to memory" << std::endl;
		close(fd);
		return 4;
	}

	for (int i = 0; i < NUM_OF_ITEMS_IN_FILE; i++)
		map[i] = 2 * i;

	if (munmap(map, FILESIZE) == -1)
	{
		std::cerr << "Failed to unmap memory" << std::endl;
		close(fd);
		return 5;
	}

	close(fd);

	return EXIT_SUCCESS;
}
