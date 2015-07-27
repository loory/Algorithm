#include <stdio.h>
#include <assert.h>

void countsort(int* array, int size, int range)
{
	int count[range];

	memset(count,0,sizeof(count));

	int i;
	for(i = 0; i < size; i++)
	{
		if (array[i] < range && array[i] >= 0)
		{
			count[array[i]]++;
		}
		else
		{
			assert(0);
		}
	}



#if 1 //why not like this,because we need know the element's pos before we insert it!
	int idx = 0;

	for(i = 0; i < range; i++)
	{
		while(count[i] > 0)
		{
			array[idx++] = i;
			count[i]--;
		}
	}
#else
	//add array index
#endif
}

int main(int argc, char **argv)
{
	int array[] = {1,3,9,4,3,2,6,2,1,3,5,1,5,7,0};
	int size = sizeof(array)/sizeof(array[0]);

	countsort(array,size,10); 

	int i = 0;
	while(size-->0) printf("%d %d\n",i++, array[i]);

	return 0;
}
