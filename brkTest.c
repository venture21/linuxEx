#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{
	char *ptr;
    
	printf("before end data seg addr : %10p\n", sbrk(0));
	if(brk(sbrk(0)+0x80000)!=0)
	   printf("brk error\n");
	printf("call brk :%10p\n",sbrk(0));

	ptr = (char*) malloc(0x40000);
	printf("ptr addr : %p\n", ptr);
	printf("after end data seg addr : %10p\n", sbrk(0));

	if(sbrk(0x1000)==(void*)-1)
		printf("sbrk error\n");
	printf("call sbrk(0x1000) : %10p\n",sbrk(0));

	if(brk(sbrk(0)+0x1000)!=0)
		printf("brk error\n");
	printf("call brk :%10p\n",sbrk(0));
	free(ptr);
    
	return 0;
}
