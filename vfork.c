#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	pid_t pid;
	int i;
	int sum1, sum2, sum;
	int exit_code;
	// 프로그램 시작시 문자열 출력
	printf("fork program starting\n");

	// fork()함수를 호출하여 자식 프로세스 생성
	pid = vfork();

	switch(pid) 
	{
		// 자식 프로세스 생성이 안된 경우
		case -1:
			perror("fork failed");
			exit(1);

		// 자식 프로세스인 경우 case 0 실행
		case 0:
			sum1=0;
			for(i=1;i<=5000;i++)
			{
				sum1+=i;
			}
			exit(0);
	}
	sum2=0;
	for(i=5001;i<=10000;i++)
	{
		sum2+=i;
	}

	sum = sum1+ sum2;

	printf("sum1=%d,  sum2=%d\n", sum1,sum2);
	printf("sum=%d\n",sum);

	return 0;
}
