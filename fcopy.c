#include <stdio.h>

#define BUFSIZE 1024

int main(int argc, char **argv)
{
    int byteCount;
    FILE *in, *out; 
    char buf[BUFSIZE];

    // 실행시 파라메터의입력(갯수)이 정상인지 확인 
    if(argc!=3) 
    {
        //write(2, "Usage : fcopy file1 file2\n",25); 
        fprintf(stderr,"Usage : fcopy file1 file2\n");
        return -1;
    }

    // 원본파일을 열기
    if((in=fopen(argv[1],"r"))==NULL)
    {
        perror(argv[1]);
        return -1;
    }

    // 대상파일을 열기
    if((out=fopen(argv[2],"w"))==NULL)
    {
        perror(argv[2]);
        return -1;
    }

    while(((byteCount = fread(buf,size(char),BUFSIZE,in))>0)
        fwrite(buf, sizeof(char), byteCount, out);

    fclose(in);
    fclose(out);

    return 0;

}



