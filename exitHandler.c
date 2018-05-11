#include <stdio.h>
#include <stdlib.h>
static void testExitHandler(int exitStatus, void *arg)
{
	printf("testExitHandler : exitStatus = %d, arg =%ld\n", exitStatus, (long)arg);
}

int main(void)
{
	// 종료 핸들러1 등록
	if (on_exit(testExitHandler, (void *) 10) != 0)
		printf("Handler error1\n");
	
	// 종료 핸들러2 등록
	if (on_exit(testExitHandler, (void *) 20) != 0)
		printf("Handler error2\n");

	// 프로그램의 시작
	printf("exit Handler Program : Start!!\n");

	// 프로그램 종료
    exit(2);
   	
}

