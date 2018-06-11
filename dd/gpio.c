#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 100

int main(int argc, char **argv)
{
	char buf[BUF_SIZE];
	int count;
	int fd=-1;

	memset(buf, 0, BUF_SIZE);

	printf("GPIO Set : %s\n", argv[1]);

	fd = open("/dev/gpioled", O_RDWR);
	if(fd<0)
	{
		printf("Error : open()\n");
		return -1;
	}	

	count = write(fd,argv[1], strlen(argv[1]));
	if(count<0)
		printf("Error : write()\n");

	count = read(fd, buf, 20);
	
	printf("Read data : %s\n", buf);

	close(fd);
	printf("/dev/gpioled closed\n");

	return 0;
}

