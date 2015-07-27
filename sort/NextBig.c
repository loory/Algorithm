#include "stdio.h"
#include "assert.h"

void swap(int *array, int lhs, int rhs)
{
	int tmp = array[lhs];
	array[lhs] = array[rhs];
	array[rhs] = tmp;
}

void print_array(int *array, int size)
{
	int i = 0;
	while(size-- > 0) printf("%d ", array[i++]);
	printf("\n");
}

int divide(int* array, int size)
{
	int pivit = 0;
	int end_of_less = 0;
	int it = 1;

	while(it < size)
	{
		if (array[it] <= array[pivit])
		{
			swap(array, it, ++end_of_less);
		}
		it++;
	}
	swap(array, pivit, end_of_less);
	return end_of_less;
}

int next_big(int* array, int size, int pos)
{
	if (pos > size)
		assert(0);

	if (size ==1)
		return array[0];
	else if (size < 1)
		assert(0);
	
	int pivit = divide(array,size);
	if (pos < pivit + 1)
	{
		return next_big(array, pivit, pos);
	}
	else if (pos > pivit + 1)
	{
		return next_big(array + pivit + 1, size - pivit -1, pos - pivit -1);
	}
	else
		return array[pivit];
}

void quicksort(int *array, int size)
{
	if (size <= 1)
		return;

	int pivit = divide(array,size);
	quicksort(array, pivit);
	quicksort(array + pivit + 1, size - pivit -1);
}

int main(int argc, char **argv)
{
	int test[] = {34,2,12,5,21,767,324,3,78,54,677,23,43};
	int size = sizeof(test)/sizeof(test[0]);
	
	int sort[size];
	memcpy(sort, test, sizeof(test));
	quicksort(sort,size);
	print_array(sort, size);

	int i = 0;
	for(i = 0; i < size; i++)
	{
		int t[size];
		memcpy(t, test, sizeof(test));
		assert(sort[i] == next_big(t, size, i + 1));	
	}


	return 0;
}
				
