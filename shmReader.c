#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE		100

int main(void)
{
	void *shared_Mem=(void*)0;
	int shmid;
	int *shmaddr;
	int i;
	
	// 1. shmget
	shmid = shmget((key_t)1234, sizeof(int)*SHMSIZE, 0666 | IPC_CREAT);
	if(shmid==-1)
	{
		fprintf(stderr,"shmget failed\n");
		exit(EXIT_FAILURE);
	}

	// 2. shmat
	shared_Mem = shmat(shmid,(void *)0, 0);
	if(shared_Mem ==(void *)-1)
	{
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}	
	
	printf("Memory attached at %X\n",(int)shared_Mem);
 	shmaddr = (int*)shared_Mem;
	

	// 3. memory access
	for(i=0;i<SHMSIZE;i++)
	{
		printf("shmaddr:%X, data:%d\n", shmaddr+i,*(shmaddr+i));
	}

	// 4. shmdt
	if(shmdt(shared_Mem)==-1)
	{
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}

	// 5. shmctl : IPC_RMID
	if(shmctl(shmid, IPC_RMID,0)==-1)
	{
		fprintf(stderr,"shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);

}

