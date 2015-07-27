#include "stdio.h"

void x(int* a, int* b)
{
	printf("%x %x", a , b);
}

int main(int argc, char **argv)
{
	int* a;
	x(a, a++);

	return 0;
}
