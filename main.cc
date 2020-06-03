#include <stdio.h>
#include "Allocator/linearallocator.h"
#include "Allocator/stackallocator.h"

#include <string.h>

#define SIZE 20
#define ALIGNMNET 8

int main()
{

	StackAllocator alloc(SIZE * sizeof(int));
	int* ptr = static_cast<int*>(alloc.Allocate(2 * sizeof(int), 8));
	if (ptr)
	{
		memset(ptr, 1, 8);
	}

	int* ptr1 = static_cast<int*>(alloc.Allocate(13, 8));
	if (ptr1)
	{
		memset(ptr1, 2, 13);
	}

	alloc.Deallocate(ptr);

	int* ptr2 = static_cast<int*>(alloc.Allocate(2 * sizeof(int), 8));
	if (ptr2)
	{
		memset(ptr2, 3, 8);
	}

	alloc.Deallocate(ptr1);
	alloc.Deallocate(ptr2);


	return 0;
}