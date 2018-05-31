/* producer.c */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#define BUFFER_SIZE PIPE_BUF
#define WRITE_SIZE 128
#define FIFO_NAME "/tmp/fifo"

void dataGen(char *buffer)
{
	int i;
	for(i=0;i<WRITE_SIZE;i++)
	{
		*(buffer+i) = i; 
	}
}

void printData(char *buffer)
{
	int i;
	for(i=0;i<WRITE_SIZE;i++)
	{
		printf("%d\n", *(buffer+i));
	}
}


int main()
{
	int pipe_fd;
	int bytes_sent = 0;
	int res;
	char buffer[BUFFER_SIZE + 1];

	printf("BUFFER_SIZE=%d\n",BUFFER_SIZE);
	printf("Process %d opening FIFO O_WRONLY\n", getpid());
	if (access(FIFO_NAME, F_OK) == -1) 
	{
		res = mkfifo(FIFO_NAME, 0777);
		if (res != 0) 
		{
			fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
			exit(EXIT_FAILURE);
		}
	}

	dataGen(buffer);
	printData(buffer);

	pipe_fd = open(FIFO_NAME, O_WRONLY);
	printf("Process %d result %d\n", getpid(), pipe_fd);
	if (pipe_fd != -1) 
	{
		while(bytes_sent < WRITE_SIZE) 
		{
			res = write(pipe_fd, buffer, WRITE_SIZE);
			if (res == -1) 
			{
				fprintf(stderr, "Write error on pipe\n");
				exit(EXIT_FAILURE);
			}
			bytes_sent += res;
		}
		(void)close(pipe_fd);
	}

	return 0;
}
