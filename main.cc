#include <stdio.h>
#include "Allocator/stackallocator.h"

#define SIZE 20
#define ALIGNMNET 8

int main()
{
	
	LinearAllocator alloc(SIZE * sizeof(int));
	int* ptr = static_cast<int*>(alloc.Allocate(sizeof(int) * 3, ALIGNMNET));

	ptr[0] = 1;
	ptr[1] = 2;
	ptr[2] = 3;
	ptr[3] = 4;
	ptr[4] = 5;


	float* ptr2 = static_cast<float*>(alloc.Allocate(sizeof(float) * 4, ALIGNMNET));

	ptr2[0] = 1.3f;
	ptr2[1] = 23.2f;
	ptr2[2] = 31.3f;
	ptr2[3] = 4.2f;

	alloc.Deallocate();
	
	
	return 0;
}