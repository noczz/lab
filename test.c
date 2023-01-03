#include <stdio.h>

int sum(int x, int y);

int x=1, y=-1, z=1;

int main()
{
	int a=1;

	if(a && sum(x, y) == 0)
		printf("if ");
	else 
		printf("else ");

	printf("a %d, z %d\n", a, z);
	return 0;
}

int sum(int x, int y)
{
	z=x+y;
	return z;
}
