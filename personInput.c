/* The sender program is very similar to msg1.c. In the main set
   up, delete the msg_to_receive declaration and replace it
   with buffer[BUFSIZ], remove the message queue delete and
   make the following changes to the running loop. We now
   have a call to msgsnd to send the entered text to the queue.
   */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "person.h"

#define DEBUG 

int main()
{
	int running = 1;
	struct person person1;
	int msgid;
	key_t keyValue;
	char buffer[BUFSIZ];

	// 버퍼 초기화
	memset(buffer, 0, BUFSIZ);

	keyValue = ftok("/home/pi",'S');

	// 메시지 큐를 생성 
	msgid = msgget(keyValue, 0666 | IPC_CREAT);

	// 메시지 큐가 정상적으로 생성되지 않은 경우
	if (msgid == -1) 
	{
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	// 사람에 대한 정보를 계속 입력한다면 반복 
	while(running) 
	{
		// 메시지 타입 = 1
		person1.msg_type = 1;

		// 이름을 입력 받고 구조체에 저장
		printf("Name : ");
		scanf("%s",person1.name);

		// 나이를 입력 받고 구조체에 저장
        printf("Age : ");
		scanf("%d",&person1.age);

		// id를 입력 받고 구조체에 저장
		printf("ID : ");
		scanf("%d",&person1.id);

		printf("continue? yes/no : ");
		scanf("%s",buffer);

        if (strncmp(buffer, "no", 2) == 0) {
			running = 0;
			person1.msg_type = 2;
		}

		if (msgsnd(msgid, (void *)&person1, sizeof(person1), 0) == -1) 
		{
			fprintf(stderr, "msgsnd failed\n");
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_SUCCESS);
}
