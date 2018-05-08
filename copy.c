#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#define BUFSIZE 1024

int main(int argc, char **argv)
{
    int byteCount, fdIn, fdOut;
    char buf[BUFSIZE];
 
    if(argc <3)
    {
        //write(2, "Usage : copy file1 file2\n", 25);
        perror("Usgae : copy file 1 file2");
        return -1;
    }

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
    
    return 0;
}
