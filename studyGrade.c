#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define DEBUG

#define MAX_VALUE 100
#define ST_NUM 200000

struct Student{
    unsigned char  name[8];
    unsigned char  kor;
    unsigned char  eng;
    unsigned char  math;
    unsigned char  sci;
    unsigned short total;
    float average;
};


int main(void)
{
    struct Student st[ST_NUM];
    unsigned long i;

    printf("struct size=%ld\n",sizeof(st));
    // 1. 난수 발생하기
    for(i=0;i<ST_NUM;i++)
    {
        // 국어
        srand(time(NULL));
        st[i].kor = (rand() % MAX_VALUE) +1;

        // 영어
        srand(time(NULL));
        st[i].eng = (rand() % MAX_VALUE) +1;

        // 수학
        srand(time(NULL));
        st[i].math = (rand() % MAX_VALUE) +1;

        // 과학 
        srand(time(NULL));
        st[i].sci = (rand() % MAX_VALUE) +1;
    }

#ifdef DEBUG
    for(i=0;i<ST_NUM;i++)
    {
        printf(" kor=%d\n eng=%d\n math=%d\n sci=%d\n",\
                st[i].kor,st[i].eng,st[i].math, st[i].sci); 
    }
#endif

    for(i=0;i<ST_NUM;i++)
    {
        st[i].total = st[i].kor + st[i].eng + st[i].math + st[i].sci;
        st[i].average = st[i].total >> 2;
    }



    return 0;
}
