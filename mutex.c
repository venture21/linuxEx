#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int count = 10;
static pthread_mutex_t countlock = PTHREAD_MUTEX_INITIALIZER;

/* increment the counter */
void* increment(void* data) 
{ 
	int error;

	while(1)
	{
		if (error = pthread_mutex_lock(&countlock))
			printf("error incr lock\n");
				//	return (void*)error;

		count++;

		if(error = pthread_mutex_unlock(&countlock))
			printf("error incr unlock\n");
			//	return (void*)error;
		usleep(10);
	}
}


/* decrement the counter */
void* decrement(void* data) 
{
	int error;
	
	while(1)
	{
		if(error = pthread_mutex_lock(&countlock))
			printf("error decr lock\n"); 
			//	return (void*)error;
		count--;
		if(error=pthread_mutex_unlock(&countlock))
			printf("error decr unlock\n");
			//	return (void*)error;
		usleep(10);
	}

}


/* retrieve the counter */
void* getcount(void* data) 
{ 
	int error;
	int countValue;
	while(1)
	{
		/*
		if (error = pthread_mutex_lock(&countlock))
			printf("error getcount lock\n");
			//	return error;
		countValue = count;
		if(error = pthread_mutex_unlock(&countlock))
			printf("error getcount unlock\n");	
		*/
		sleep(1);
		printf("count = %d\n",count);
	}
}


int main(int argc, char *argv[])
{
	pthread_t p_thread[3];
	int err;

	if((err = pthread_create(&p_thread[0], NULL, increment, NULL) < 0))
	{
		perror("incr thread create error : ");
	    exit(1);
	}

	if((err = pthread_create(&p_thread[1], NULL, decrement, NULL) < 0))
	{
	    perror("incr thread create error : ");
	    exit(1);
	}

	
    if((err = pthread_create(&p_thread[2], NULL, getcount, NULL) < 0))
	{
		perror("incr thread create error : ");
		exit(1);
	}
	
	err = pthread_detach(p_thread[0]);
	err = pthread_detach(p_thread[1]);
	err = pthread_detach(p_thread[2]);

	while(1);

	return 0;

}


