#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

	// Remove old queues if they exist
	int tempQueue;
	if ((tempQueue = msgget(QUEUE_KEY_USER1, 0)) != -1)
		msgctl(tempQueue, IPC_RMID, NULL);
	if ((tempQueue = msgget(QUEUE_KEY_USER2, 0)) != -1)
		msgctl(tempQueue, IPC_RMID, NULL);

	// Create new message queues
	if ((user1Queue = msgget(QUEUE_KEY_USER1, IPC_CREAT | 0666)) == -1)
	{
		perror("User1: msgget error");
		return (1);
	}
	if ((user2Queue = msgget(QUEUE_KEY_USER2, IPC_CREAT | 0666)) == -1)
	{
		perror("User2: msgget error");
		return (1);
	}

	while (1)
	{
		// Prompt for input from User1
		printf("USER 1: ");
		fgets(msg.mtext, MAX_MSG_SIZE, stdin);
		msg.mtype = 1;
		msglen = strlen(msg.mtext) + 1;

		// Send message to User2
		if (msgsnd(user1Queue, &msg, msglen, 0) == -1)
		{
			perror("Not able to send message to User 2");
			continue;
		}

		// Wait for response from User2
		if (msgrcv(user2Queue, &msg, MAX_MSG_SIZE, 1, 0) == -1)
		{
			perror("Error receiving from User 2");
			continue;
		}
		printf("USER 2: %s\n", msg.mtext);
	}

	return 0;
}
