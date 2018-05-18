#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>
#define BUFSIZE 1024

int main(int argc, char **argv)
{
    int byteCount, fdIn, fdOut;
    char buf[BUFSIZE];
 	struct timeval StartTime, EndTime, ProcTime;

    if(argc <3)
    {
        //write(2, "Usage : copy file1 file2\n", 25);
        perror("Usgae : copy file 1 file2");
        return -1;
    }

	gettimeofday(&StartTime, NULL);
    // 원본파일 열기
    if((fdIn = open(argv[1], O_RDONLY))<0)
    {
        perror(argv[1]);
        return -1;
    }

    // 새로 생성되는 파일 열기
    if((fdOut = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR))<0)
    {
        perror(argv[2]);
        return -1;
    }

    while((byteCount=read(fdIn,buf,sizeof(buf)))>0)
        write(fdOut, buf, byteCount);

    close(fdIn);
    close(fdOut);
    
	gettimeofday(&EndTime, NULL);

	if((EndTime.tv_usec-StartTime.tv_usec)<0)
	{
		ProcTime.tv_sec  = EndTime.tv_sec - StartTime.tv_sec - 1;
		ProcTime.tv_usec = 1000000 + EndTime.tv_usec - StartTime.tv_usec;
	} 
	else
	{
		ProcTime.tv_sec  = EndTime.tv_sec - StartTime.tv_sec;
		ProcTime.tv_usec = EndTime.tv_usec - StartTime.tv_usec; 
	}

	printf("Copy Time : %ld.%ldusec\n",ProcTime.tv_sec, ProcTime.tv_usec);
    return 0;
}
