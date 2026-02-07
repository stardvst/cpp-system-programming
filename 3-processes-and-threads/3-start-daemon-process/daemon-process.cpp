#include <iostream>
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
	pid_t child;
	int status;

	std::cout << "I'm the parent process, my pid is: " << getpid() << std::endl;
	std::cout << "My parent process's pid is: " << getppid() << std::endl;
	std::cout << "I'm going to create a child process..." << std::endl;

	child = fork();

	if (child == -1)
	{
		std::cerr << "Failed to fork process" << std::endl;
		return EXIT_FAILURE;
	}

	if (child == 0)
	{
		std::cout << "  I'm the child process, my pid is: " << getpid() << std::endl;
		std::cout << "  My parent process's pid is: " << getppid() << std::endl;
		std::cout << "  I'm going to create a daemon process..." << std::endl;

		setsid();
		if (chdir("/") == -1)
		{
			std::cerr << "Failed to change working directory to /" << std::endl;
			return EXIT_FAILURE;
		}

		// run daemon process
		sleep(10);
	}

	return EXIT_SUCCESS;
}
