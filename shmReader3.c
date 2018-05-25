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
    if(signo==SIGUSR1)
       printf("SIGUSR1\n");
}


int main(void)
{
	void *shared_Mem=(void*)0; 
	struct pidSt pidSt1;
	int shmid, msqid;
	pid_t pid;
	int *shmaddr;
	int i;
	long msg_to_receive=0;
	key_t keyValue;
	
	// STEP 0. ftok()로 키값 생성
	keyValue = ftok(STRING, PROJ_ID);

	// STEP 4. 시그널 핸들러 등록
	signal(SIGUSR1, sigHandler);

	// STEP 1.1 shmget
	shmid = shmget((key_t)12345, sizeof(int)*SHM_SIZE, 0666 | IPC_CREAT);
	if(shmid==-1)
	{
		fprintf(stderr,"shmget failed\n");
        	exit(EXIT_FAILURE);
	}

	// STEP 1.2 shmat
	shared_Mem = shmat(shmid,(void *)0, 0);
	if(shared_Mem ==(void *)-1)
	{
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}
					    
	printf("Memory attached at 0x%p\n",shared_Mem);
	shmaddr = (int*)shared_Mem;

	// 자신의 PID값을 공유 메모리에 저장
	*(shmaddr+4)=getpid();
	*(shmaddr+8)=1;
    	

	pid = *(shmaddr);
	
	printf("shmWriter3 pid=%d\n", pid);
	printf("shmReader3 pid=%d\n", *(shmaddr+4));

	if(shmdt(shared_Mem)==-1)
	{
	    fprintf(stderr,"shmdt failed\n");
	    exit(EXIT_FAILURE);
	}

	if(shmctl(shmid, IPC_RMID,0)==-1)
	{
		fprintf(stderr,"shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	
    
	printf("shmReader2 pid=%d\n", pid);

	kill(pid, SIGUSR2);

	pidSt1.msg_type = 1;
    pidSt1.pid =getpid();

	if (msgsnd(msqid, (void *)&pidSt1, sizeof(pidSt1), 0) == -1)
	{
		fprintf(stderr, "msgsnd failed\n");
		exit(EXIT_FAILURE);
	}

	// STEP 6.1 shmget
	shmid = shmget((key_t)1234, sizeof(int)*SHMSIZE, 0666 | IPC_CREAT);
	if(shmid==-1)
	{
		fprintf(stderr,"shmget failed\n");
		exit(EXIT_FAILURE);
	}

	// STEP 6.2 shmat
	shared_Mem = shmat(shmid,(void *)0, 0);
	if(shared_Mem ==(void *)-1)
	{
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}	
	
	printf("Memory attached at %p\n",shared_Mem);
 	shmaddr = (int*)shared_Mem;
	
	pause();

	// STEP 6.3 memory access
	for(i=0;i<SHMSIZE;i++)
	{
		printf("shmaddr:%p, data:%d\n", shmaddr+i,*(shmaddr+i));
	}

	// STEP 6.4 shmdt
	if(shmdt(shared_Mem)==-1)
	{
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}

	// STEP 6.5 kill()
	kill(pid, SIGUSR1);

	exit(EXIT_SUCCESS);

}

