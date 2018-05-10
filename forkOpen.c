#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 30

int main()
{
	pid_t pid;
	char *message;
	int n;
	int fd;
	int exit_code;
	// 프로그램 시작시 문자열 출력
	printf("fork file open test program starting\n");

	message = malloc(STR_SIZE);
	memset(message, 0, STR_SIZE);
	fd = open("./test.txt", O_RDWR | O_CREAT | O_TRUNC,
			 S_IRWXU | S_IWGRP | S_IRGRP | S_IROTH);

	// fork()함수를 호출하여 자식 프로세스 생성
	pid = fork();

	switch(pid) 
	{
		// 자식 프로세스 생성이 안된 경우
		case -1:
			perror("fork failed");
			exit(1);

		// 자식 프로세스인 경우 case 0 실행
		case 0:
			sprintf(message,"This is the child\n");

			n = 5;
			exit_code = 37;
			break;
		// 부모 프로세스인 경우 default 실행
		default:
			sprintf(message,"This is the parent\n");
			n = 3;
			exit_code = 0;
			break;
	}

	for(; n > 0; n--) 
	{
		write(fd,message,strlen(message));
		sleep(1);
	}

	// 부모 프로세스인 경우 if문 실행
	if (pid != 0) 
	{
		int status;
		pid_t child_pid;

		// wait()함수를 통해 자식 프로세스가 끝나기를 기다림
		child_pid = wait(&status);
		printf("Child has finished: PID = %d\n", child_pid);

		// 정상 종료인 경우
		if (WIFEXITED(status))
		    printf("normal termination, exit status = %d\n", WEXITSTATUS(status));

		// 시그널에 의해서 종료된 경우
		else if (WIFSIGNALED(status))
		    printf("abnormal termination, signal number = %d%s\n",WTERMSIG(status),
					WCOREDUMP(status) ? "(core file generated)" : "");
		else if (WIFSTOPPED(status))
		    printf("child stopped, signal number = %d\n", WSTOPSIG(status));
	}
		exit(exit_code);
}
