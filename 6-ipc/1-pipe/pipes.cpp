#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const char *msg1 = "Message sent from Child to Parent";
const char *msg2 = "Message sent from Parent to Child";
#define MSGSIZE 34
#define IN 0
#define OUT 1

int main()
{
	char inbufToParent[MSGSIZE];
	char inbufToChild[MSGSIZE];
	int childToParent[2], parentToChild[2];
	int pid, nbytes;

	inbufToChild[0] = '\0';
	inbufToParent[0] = '\0';

	if (pipe(childToParent) < 0)
	{
		perror("pipe");
		return 1;
	}

	if (pipe(parentToChild) < 0)
	{
		perror("pipe");
		return 1;
	}

	if ((pid = fork()) > 0)
	{
		printf("Created child process with pid: %d\n", pid);
		close(childToParent[IN]); // must close unused end of the pipe
		write(childToParent[OUT], msg1, strlen(msg1));
		close(childToParent[OUT]);

		close(parentToChild[OUT]);

		nbytes = read(parentToChild[IN], inbufToChild, strlen(msg2));
		inbufToChild[nbytes] = '\0';
		printf("Child received message: %s\n", inbufToChild);
		close(parentToChild[IN]);
		wait(NULL);
	}
	else
	{
		close(childToParent[OUT]);
		nbytes = read(childToParent[IN], inbufToParent, strlen(msg1));
		inbufToParent[nbytes] = '\0';
		printf("Parent received message: %s\n", inbufToParent);
		close(childToParent[IN]);

		close(parentToChild[IN]);
		write(parentToChild[OUT], msg2, strlen(msg2));
		close(parentToChild[OUT]);
	}
}
