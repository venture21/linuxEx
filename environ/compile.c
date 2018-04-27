#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int main(void)
{
   char strDIR[30];
   char strNAME[15];
   char strResult[45];

   sprintf(strDIR,"%s", getenv("FILEDIR"));
   sprintf(strNAME,"%s",getenv("FILENAME"));
   sprintf(strResult,"gcc -o hello ");
   strcat(strResult,strDIR);
   strcat(strResult,strNAME);
   // gcc -o hello /home/venture/linuxEx/hello.c
   system(strResult);      
   system("./hello");
   return 0;
}
