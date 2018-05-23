#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
	int data_processed;
	int status;

	// 입력과 출력을 위한 2개의 PIPE를 위해 배열로 선언
	int file_pipes[2];
	const char some_data[] = "123";
	char buffer[BUFSIZ + 1];
	pid_t fork_result;
	memset(buffer, '\0', sizeof(buffer));

	if (pipe(file_pipes) == 0) 
	{
		fork_result = fork();
		if (fork_result == -1) { // fork fail
				fprintf(stderr, "Fork failure");
				exit(EXIT_FAILURE);
		}
		if (fork_result == 0) { // child process
				sprintf(buffer, "%d", file_pipes[0]);
				execl("pipe4", "pipe4", buffer, (char *)0);
				exit(EXIT_FAILURE);
		}
		else { // parent process
				data_processed = write(file_pipes[1], some_data, strlen(some_data));
				printf("%d - wrote %d bytes\n", getpid(), data_processed);
		}
	}

	wait(&status);

	exit(EXIT_SUCCESS);
}
