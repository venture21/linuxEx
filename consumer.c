/* consumer.c */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE PIPE_BUF
#define FIFO_NAME "/tmp/fifo"

int main()
{
	int pipe_fd, res;
	int open_mode = O_RDONLY;
	char buffer[BUFFER_SIZE + 1];
	int bytes_read = 0;
	memset(buffer, '\0', sizeof(buffer));
	printf("Process %d opening FIFO O_RDONLY\n", getpid());
	if (access(FIFO_NAME, F_OK) == -1) 
	{
		res = mkfifo(FIFO_NAME, 0777);
		if (res != 0) 
		{
			fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
			exit(EXIT_FAILURE);
		}
	}

	pipe_fd = open(FIFO_NAME, open_mode);
	printf("Process %d result %d\n", getpid(), pipe_fd);
	if (pipe_fd != -1) 
	{
		do 
		{
				res = read(pipe_fd, buffer, BUFFER_SIZE);
				bytes_read += res;
		} while (res > 0);
		
		(void)close(pipe_fd);
	}
	else 
	{
		exit(EXIT_FAILURE);
	}
}
