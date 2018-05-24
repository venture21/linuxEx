/* Here's the receiver program. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "person.h"
#include <fcntl.h>

#define FILE_NAME "test.bin"

int main()
{
	int running = 1;
	int msgid;
	int fd, size;
	key_t keyValue;
	struct person person1;
	long int msg_to_receive = 0;

	keyValue = ftok(STRING, PROJ_ID);

	/* First, we set up the message queue. */
	msgid = msgget(keyValue, 0666 | IPC_CREAT);
	if (msgid == -1) 
	{
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	/*  Then the messages are retrieved from the queue, until an
   		end message is encountered.
		Lastly, the message queue is deleted. */

	fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_EXCL, 0666);
	if(fd<0)
	{
		fprintf(stderr, "can't open test.bin : %d\n", errno);
		exit(EXIT_FAILURE);
	}

	while(running) 
	{
		if (msgrcv(msgid, (void *)&person1, BUFSIZ,
			msg_to_receive, 0) == -1) 
		{
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		printf("type:%ld\n", person1.msg_type);
		printf("name:%s\n", person1.name);
		printf("age:%d\n", person1.age);
		printf("id:%d\n", person1.id);

		size = write(fd, &person1, sizeof(person1));

		if(size<0)
			fprintf(stderr, "Error : write() %d\n", errno);

		if (person1.msg_type==2) 
		{
			running = 0;
		}
	}
	close(fd);

	if (msgctl(msgid, IPC_RMID, 0) == -1) 
	{
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
