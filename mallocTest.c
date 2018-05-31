#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define DSIZE 0x30000

struct name
{
    int     age;
    char    name[DSIZE];
};
int main()
{           
    char *org_name;
    struct name *myname;
    int i;
					                       
    // org_name 에 char 이 25만큼 들어갈수 있는
    // 메모리 공간을 할당한다.                                                
    // malloc 는 할당된 메모리 영역의 포인터를 리턴해주므로
    // org_name 은 malloc 를 이용해 할당된 영역의 포인터를 가르키게 된다.
    org_name = (char *)malloc(sizeof(char)*DSIZE);
 	if(org_name==NULL)
		printf("Error :malloc()\n"); 

    // myname 역시 마찬가지로 struct name 이 2개 만큼 들어갈수
    // 있는 메모리 공간을 할당한다.
    myname = (struct name *)malloc(sizeof(myname)*2);                         

	strcpy(org_name, "yundream");
						                                                            myname[0].age = 25;
	strcpy(myname[0].name, org_name);
	strcpy(org_name, "testname");                                             
	myname[1].age = 28;                                                       
	strcpy(myname[1].name, org_name);                                          
												                     
	for(i = 0; i < 2; i++)
	{                           
		printf("%d : %s\n", myname[i].age, myname[i].name);
	}                                                                         
}
