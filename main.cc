#include <stdio.h>
#include "Allocator/linearallocator.h"
#include "Allocator/stackallocator.h"

#define SIZE 20
#define ALIGNMNET 8

int main()
{

	StackAllocator alloc(SIZE * sizeof(int));

	alloc.Allocate(3 * sizeof(int), 8);
	
	
	
	return 0;
}