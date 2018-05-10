#include <stdio.h>

extern int add(int a, int b);
extern int sub(int a, int b);
extern int mul(int a, int b);
extern int div(int a, int b);

int main(void)
{
	int a, b, c;

	c = add(a,b);
	c = sub(a,b);
	c = mul(a,b);
	c = div(a,b); 

	return 0;
}


