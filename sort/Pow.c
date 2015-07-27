#include <stdio.h>

long pow(int x, unsigned int y)
{
	if (y == 0)
		return 1;
	else if (y == 1)
		return x;
	else
	{
		int m = y/2;
		long s = pow(x,m);
		if (y % 2 == 0)
			return s*s;
		else
			return s*s*x;
	}
}

int main(int argc, char** argv)
{
	printf("%d\n",pow(2,20));	
	return 0;
}
