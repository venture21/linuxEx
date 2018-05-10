#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
		printf(“Running ps with system\n”);
		system(“ps -ax”);
		printf(“Done.\n”);
		sleep(10);
		exit(0);
}
