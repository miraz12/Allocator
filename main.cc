#include "Allocator/linearallocator.h"
#include "Allocator/stackallocator.h"

constexpr int ALLOCSIZE = 20;
constexpr int ALIGNMENT = 8;

int main()
{
	StackAllocator alloc(ALLOCSIZE * sizeof(int));
	//LinearAllocator alloc(ALLOCSIZE * sizeof(int));
	int* ptr = static_cast<int*>(alloc.Allocate(2 * sizeof(int), ALIGNMENT));
	if (ptr)
	{
		memset(ptr, 1, 8);
	}
	
	int* ptr1 = static_cast<int*>(alloc.Allocate(13, 8));
	if (ptr1)
	{
		memset(ptr1, 2, 13);
	}
	
	//alloc.Deallocate(ptr1);
	int* ptr2 = static_cast<int*>(alloc.Allocate(2 * sizeof(int), 8));
	if (ptr2)
	{
		memset(ptr2, 3, 8);
	}
	
	alloc.Deallocate(ptr1);
	alloc.Deallocate(ptr2);
	alloc.Deallocate(ptr);
	
	return 0;
}