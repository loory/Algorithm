#include <stdio.h>
#include <assert.h>
#include <string.h>

#define long long long
long fib_array[2][2] = 
{
	{1,1},
	{1,0}
};

long tmp[2][2];

void print_matrix(long *m)
{
#if 1 	
	printf("=====%x=====\n\
			[%d,%d]\
			[%d,%d]\n"
			,m,m[0],m[1],m[2],m[3]);
#endif 
}
#define print_matrix(x) p(x)
void p(long* a)
{

}


long* multi_matrix22(long *lhs, long *rhs)
{
	int i,j,k;
	long t_lhs[2][2];
	long t_rhs[2][2];

	memcpy(t_lhs, lhs, sizeof(t_lhs));
	memcpy(t_rhs, rhs, sizeof(t_rhs));

	for(i = 0;i < 2; i ++)
	{
		for(j = 0; j < 2; j ++)
		{
			tmp[i][j] = 0;
			for(k = 0; k < 2; k ++)
			{
				tmp[i][j] += t_lhs[i][k]*t_rhs[k][j]; //todo big num plus 
			}
		}
	}
	print_matrix(&tmp[0][0]);	
	return &tmp[0][0];
}

long* multi_fib_array(unsigned int n)
{
	if (n == 1)
		return (long*)fib_array;
	else
	{
		int m = n / 2;
		long* s = multi_fib_array(m);
		if ((n % 2) == 0)
			return multi_matrix22(s,s);
		else
			return multi_matrix22(multi_matrix22(s,s),(long*)fib_array);
	}
}

long fib(unsigned int y)
{
	if (y == 0)
		return 0;
	else if (y == 1)
		return 1;
	else
	{
		long *s = multi_fib_array(y);


		return s[1];
	}
}

int main(int argc, char** argv)
{
	int i = 0;
	long smaller = 0;
	long biger = 1;

	for(i = 2; i < 100;i++)
	{
		long fib_i = smaller + biger;
		smaller = biger;
		biger = fib_i;
		printf("Fib(%d) is %lld\n",i, fib_i);
		assert(fib_i == fib(i));
	}

	return 0;
}
