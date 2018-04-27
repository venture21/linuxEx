#include <stdio.h>
#include <string.h>

#define DEBUG 

int main(void)
{
    int i;
    char strInput[51];
    int strSize;

    // 1. 문자열을 입력받는다.(최대50 문자+NULL문자)
    scanf("%s",strInput);

#ifdef DEBUG 
        printf("%s\n", strInput);
#endif
    
    // 2. 입력받은 문자열이 영문소문자인지 확인한다.
    //    그 이외의 입력을 받게되면 메세지를 출력하고 종료
    strSize = strlen(strInput);
    for(i=0;i<strSize;i++)  
    {
        if(!(strInput[i]>='a' && strInput[i]<='z'))
        {
           printf("Error : strInput\n");  
           return -1;
        }
    }
#ifdef DEBUG
    printf("strInput is OK\n");
#endif

    // 3. 팰린드롬인지 확인한다.
    if(strSize%2)
        printf("strSize is odd\n");
    else
        printf("strSize is even\n");

    for(i=0;i<(strSize>>1);i++)
    {
        if(!(strInput[i]==strInput[strSize-1-i]))
        {
            printf("strInput is not palindrome\n");
            return -1;
        }

    }
    printf("strInput is palindrome\n");


   
    return 0;
}


