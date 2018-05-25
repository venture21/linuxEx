#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <signal.h>
#include <wait.h>

#define SHM_SIZE 2
#define COUNT_VALUE 10

int main(void)
{
	void *shared_Mem=(void*)0;
	int shmid;
	int count;
	int *shmaddr;
	int status;
	pid_t pid;

	// 공유 메모리 생성(물리 메모리 공간 할당)
	shmid = shmget((key_t)0X12345, sizeof(int)*SHM_SIZE, 0666 | IPC_CREAT);
	if(shmid==-1)
	{
		fprintf(stderr,"shmget failed\n");
		exit(EXIT_FAILURE);
	}

	// 내 프로세스에 할당받은 메모리 공간을 붙이기
	shared_Mem = shmat(shmid,(void *)0, 0);
	if(shared_Mem ==(void *)-1)
	{
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}

	// void포인터의 주소값을 int 포인터에게 전달
	shmaddr = (int*)shared_Mem;


	// 자식 프로세스 생성
	pid = fork();

	// fork()호출에 실패했을때
	if(pid==-1)
		fprintf(stderr, "Erro : fork()\n");
	
	// 자식 프로세스인 경우
	else if(pid==0)
	{
		// COUNT_VALUE값에 도달하면 종료 
		while(*(shmaddr+1)<COUNT_VALUE)
		{
			if((*shmaddr)==1)
			{
				count = *(shmaddr+1);
				*(shmaddr+1) = count + 1;
				printf("count=%d\n",*(shmaddr+1));
				sleep(1);
				*shmaddr = 0;
			}
		}

		// 더 이상 메모리에 대한 접근이 필요하지 않으므로
		// 자식 프로세스 메모리에서 detach
		if(shmdt(shared_Mem)==-1)
		{
			fprintf(stderr,"shmdt failed\n");
			exit(EXIT_FAILURE);
		}
		exit(0);
	}
	// 부모 프로세스인 경우
	else
	{
        while(*(shmaddr+1)<COUNT_VALUE)
		{
			if((*shmaddr)==0)
			{
				count = *(shmaddr+1);
				*(shmaddr+1) = count + 1;
				printf("count=%d\n",*(shmaddr+1));
			    sleep(1);
				*shmaddr = 1;
			}
		}
	}

	// 부모 프로세스의 메모리 detach
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

	wait(&status);
	return 0;
}
