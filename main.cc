#include "Allocator/linearallocator.h"
#include "Allocator/stackallocator.h"
#include "Allocator/poolallocator.h"

constexpr int ALLOCSIZE = 70;
constexpr int ALIGNMENT = 8;

int main()
{
	PoolAllocator alloc(8, sizeof(int) * 10, ALLOCSIZE * sizeof(int));
	//LinearAllocator alloc(ALLOCSIZE * sizeof(int));
	int* ptr = static_cast<int*>(alloc.Allocate(10 * sizeof(int), ALIGNMENT));
	if (ptr)
	{
		memset(ptr, 1, 10 * sizeof(int));
	}
	
	int* ptr1 = static_cast<int*>(alloc.Allocate(10 * sizeof(int), ALIGNMENT));
	if (ptr1)
	{
		memset(ptr1, 2, 10 * sizeof(int));
	}
	alloc.Deallocate(ptr);
	
	//alloc.Deallocate(ptr1);
	int* ptr2 = static_cast<int*>(alloc.Allocate(10 * sizeof(int), ALIGNMENT));
	if (ptr2)
	{
		memset(ptr2, 3, 10 * sizeof(int));
	}

	int* ptr3 = static_cast<int*>(alloc.Allocate(10 * sizeof(int), ALIGNMENT));
	if (ptr3)
	{
		memset(ptr3, 3, 10 * sizeof(int));
	}
	
	alloc.Deallocate(ptr1);
	alloc.Deallocate(ptr2);
	
	return 0;
}