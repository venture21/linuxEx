#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// SIGINT
static void sigHandler1(int signo)
{
    printf("signal no : %d\n", signo); 
}

// SIGQUIT
static void sigHandler2(int signo)
{
    printf("signal no : %d\n", signo);
}


int main(void)
{
	struct sigaction act;
    sigset_t newmask, oldmask, pendmask;
    act.sa_handler = sigHandler1;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if(sigaction(SIGINT, &act, 0)==-1)
	    printf("can't catch SIGINT\n");

	act.sa_handler = sigHandler2;
	if(sigaction(SIGQUIT, &act, 0)==-1)
        printf("can't catch SIGQUIT\n");
                
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask)<0)
            printf("SIG_BLOCK error\n");
	printf("SIGQUIT is blocked\n");
	sleep(10);
    
	if(sigpending(&pendmask)<0)
        printf("sigpending error\n");
 
	if(sigismember(&pendmask, SIGQUIT))
		printf("SIGQUIT pending\n");

    if(sigprocmask(SIG_SETMASK, &oldmask, NULL)<0)
        printf("SIG_SETMASK error");
    printf("SIGQUIT is unblocked\n");
    
    sleep(5);
    exit(0);
 }
