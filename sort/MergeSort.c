#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>

void Combine(int* head, int* mid, int* tail)
{
	int* temp = malloc(tail-head+1);
	int* tmp = temp; 
	if (!tmp)
		assert("1213213");

	int* lhs = head;
	int* rhs = mid + 1;

	while(lhs <= mid && rhs <= tail)
	{
		if (*lhs <= *rhs)
		{
			*tmp = *lhs;
			lhs++;
		}
		else
		{
			*tmp = *rhs;
			rhs++;
		}
		tmp++;			
	}
	if (lhs <= mid)
	{
		memcpy(tmp, lhs, (mid-lhs+1)*sizeof(int));
	}
	else if (rhs <= tail)
	{
		memcpy(tmp, rhs, (tail-rhs+1)*sizeof(int));
	}
	memcpy(head, temp, (tail - head + 1)*sizeof(int));

	if (temp)
	{
		free(temp);
	}
}

void MergeSub(int* head, int* tail)
{
	printf("head %d tail %d\n", *head, *tail);
	if (head < tail)
	{
		int* mid  = head + (tail - head)/2;	
		MergeSub(head, mid);
		MergeSub(mid + 1, tail);
		Combine(head, mid, tail);
	}
}

void MergeSort(int* array, unsigned int size)
{
	printf("MergeSort %x %d", array, size);
	if (!array || size <=1)
		return;
	MergeSub(array, array + size - 1);	
}

int main(int argc, char** argv)
{
	int i;
	int a[] = {99,1,3,76,22,30,50,23};

	MergeSort(a, sizeof(a)/ sizeof (a[0]));
	
	for(i = 0; i < sizeof (a)/sizeof(a[0]); i ++)
	{
		printf("%d %d \n",i,a[i]);
	}
	return 0;
}
