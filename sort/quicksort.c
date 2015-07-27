#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* array, int lhs, int rhs)
{
	int temp = array[lhs];
	array[lhs] = array[rhs];
	array[rhs] = temp;
}

void print_array(int *array, int size)
{
	printf("array ");
	int i = 0;
	while(size-- > 0){printf("%d ",array[i++]);}
	printf("\n");
}

int conquer(int *array, int size)
{
	int piovt_pos = 0;
	int less_end = 0;
	int it = 1;
	int piovt = array[0];

	while(it < size)
	{
		if (array[it] < piovt)
		{
			swap(array, it, ++less_end);
		}
		it ++;
	}
	swap(array, piovt_pos, less_end);
	
	return less_end;
}

void quicksort(int *array, int size)
{
	print_array(array, size);
	if (!array)
		return;

	if (size <2)
	{
		return;
	}

    int less_end = conquer(array,size);
	quicksort(array, less_end);
	quicksort(array + less_end +1, size - less_end - 1);
}

int main(int argc, char **argv)
{
	int i = 0;
	int array[] = { 99, 7, 2,3, 55,12,44,23,33};
	
	srand((unsigned int)time((void*)0));
	int r = rand()%sizeof(array)/sizeof(array[0]);
	swap(array, 0, r);
	quicksort(array, sizeof(array)/sizeof(array[0]));
	
	for(i = 0; i < sizeof(array)/sizeof(array[0]);i++)
	{
		printf("%d %d \n",i, array[i]);
	}

	return 0;
}
