#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

volatile sig_atomic_t quitflag;

static void sig_int(int signo)
{
	if(signo==SIGINT)
		printf("Interrupt\n");
	else if(signo==SIGQUIT)
		quitflag=1;
}

int main(void)
{
	sigset_t newmask, oldmask, zeromask;

	if(signal(SIGINT, sig_int)==SIG_ERR)
		printf("signal(SIGINT) error");
	if(signal(SIGQUIT, sig_int)==SIG_ERR)
		printf("signal(SIGQUIT) error");
	sigemptyset(&zeromask);
	//sigaddset(&zeromask, SIGQUIT);
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGQUIT);

	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask)<0)
		printf("SIG_BLOCK error");
	quitflag = 0;

	while(quitflag==0)
		sigsuspend(&zeromask);

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL)<0)
		printf("SIG_SETMASK error");
	abort();
	exit(0);
}
