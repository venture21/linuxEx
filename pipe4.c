#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
		int fd;
		int data_processed;
		char buffer[BUFSIZ + 1];
		int file_descriptor;
		fd = open("pipe1.c",O_RDONLY);
		printf("fd=%d\n",fd);
		memset(buffer, '\0', sizeof(buffer));
		sscanf(argv[1], "%d", &file_descriptor);
		data_processed = read(file_descriptor, buffer, BUFSIZ);
		printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
		exit(EXIT_SUCCESS);
}
