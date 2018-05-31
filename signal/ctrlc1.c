#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sigHandler(int sig)
{
	static int counter=0;
	printf("OUCH! - I gotsignal %d\n",sig);
	counter++;
	if(counter==5)
		(void)signal(SIGQUIT,SIG_DFL);
}

int main()
{
	if(signal(SIGQUIT, sigHandler)==SIG_ERR)
		printf("Failed call signal()\n");

	while(1)
	{
		printf("Hello world!\n");
		sleep(5);
	}
	return 0;
} 
