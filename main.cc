#include <cstdint>
#include <stdio.h>
#include "Allocator/linearallocator.h"
#include <stdlib.h>




int main()
{
	int *ptr = (int*)malloc(10 * sizeof(int));
	LinearAllocator alloc(10*sizeof(int), ptr);

	alloc.Allocate(8, 8);


	ptr[1] = 1;

	printf("Hell World!");
}