#include<stdio.h>

int square(int x)
{
	return x * x;
} 

double add(int x, int y)
{
	return (square(x) + square(y));
}


int main(void)
{
	int x = 2;
	int y = 3;
	double result=0;

	result = add(x,y);

	printf("%lf\n",result);
}
