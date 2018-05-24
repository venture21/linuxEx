#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <signal.h>
#include "shm.h"

#define SHMSIZE		100

static void sigHandler(int signo)
{
	if(signo==SIGUSR2)
		printf("SIGUSR2\n");
	else if(signo==SIGUSR1)
		printf("SIGUSR1\n");
}


int main(void)
{
	void *shared_Mem=(void*)0;
	struct pidSt pidSt1;
	pid_t pid;
	int shmid, msqid;
	int *shmaddr;
	int i;
	long msg_to_receive = 0;
	
	key_t keyValue;

	// STEP 0. ftok()로 키값 생성
	keyValue = ftok(STRING, PROJ_ID);

	// STEP 4. 시그널 핸들러 등록
	signal(SIGUSR1, sigHandler);
	signal(SIGUSR2, sigHandler);

	// STEP 1. 메세지 큐를 생성하고 메세지 전송
	msqid = msgget(keyValue, 0666 | IPC_CREAT);
	if(msqid == -1)
	{
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	pidSt1.msg_type = 1;
	pidSt1.pid =getpid(); 

	if (msgsnd(msqid, (void *)&pidSt1, sizeof(pidSt1), 0) == -1)
	{
		fprintf(stderr, "msgsnd failed\n");
		exit(EXIT_FAILURE);
	}

	// shmReader2.c에서 signal을 전송하기 전까지 pause
	pause();
	printf("test1\n");

	// STEP 3. shmReader2의 pid값을 확인
    if (msgrcv(msqid, (void *)&pidSt1, sizeof(pidSt1), msg_to_receive, 0) == -1)
	{
		fprintf(stderr, "msgrcv failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	pid = pidSt1.pid;
    printf("shmReader2 pid=%d\n", pid);

	if (msgctl(msqid, IPC_RMID, 0) == -1)
	{
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}



	// STEP 5.1 shmget
	shmid = shmget((key_t)1234, sizeof(int)*SHMSIZE, 0666 | IPC_CREAT);
	if(shmid==-1)
	{
		fprintf(stderr,"shmget failed\n");
		exit(EXIT_FAILURE);
	}

	// STEP 5.2 shmat
	shared_Mem = shmat(shmid,(void *)0, 0);
	if(shared_Mem ==(void *)-1)
	{
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}	
	
	printf("Memory attached at 0x%p\n",shared_Mem);
 	shmaddr = (int*)shared_Mem;

	// STEP 5.3 memory access
	for(i=0;i<SHMSIZE;i++)
	{
		*(shmaddr+i)=i+1;
		printf("shmaddr:%p, data:%d\n", shmaddr+i,*(shmaddr+i));
	}

	kill(pid, SIGUSR1);

	// STEP 7.1 shmdt
	if(shmdt(shared_Mem)==-1)
	{
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}

	pause();

	// STEP 7.2 shmctl : IPC_RMID
	if(shmctl(shmid, IPC_RMID,0)==-1)
	{
		fprintf(stderr,"shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);

}

