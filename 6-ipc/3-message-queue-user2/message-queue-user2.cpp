#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_MSG_SIZE 256
#define QUEUE_KEY_USER1 1001
#define QUEUE_KEY_USER2 1002

struct message
{
	long mtype;
	char mtext[MAX_MSG_SIZE];
};

int main()
{
	int user1Queue, user2Queue;
	struct message msg;
	int msglen;

	// Wait for User1 to create and clean queues
	sleep(1);

	// Create/get message queues
	if ((user1Queue = msgget(QUEUE_KEY_USER1, IPC_CREAT | 0666)) == -1)
	{
		perror("User2: msgget error for user1Queue");
		return (1);
	}
	if ((user2Queue = msgget(QUEUE_KEY_USER2, IPC_CREAT | 0666)) == -1)
	{
		perror("User2: msgget error for user2Queue");
		return (1);
	}

	while (1)
	{
		// Wait for message from User1
		if (msgrcv(user1Queue, &msg, MAX_MSG_SIZE, 1, 0) == -1)
		{
			perror("Error receiving from User 1");
			continue;
		}
		printf("USER 1: %s\n", msg.mtext);

		// Prompt for input from User2
		printf("USER 2: ");
		fgets(msg.mtext, MAX_MSG_SIZE, stdin);
		msg.mtype = 1;
		msglen = strlen(msg.mtext) + 1;

		// Send message to User1
		if (msgsnd(user2Queue, &msg, msglen, 0) == -1)
		{
			perror("Not able to send message to User 1");
			continue;
		}
	}

	return 0;
}
