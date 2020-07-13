#include "Allocator/linearallocator.h"
#include "Allocator/stackallocator.h"
#include "Allocator/poolallocator.h"
#include "Allocator/freelistallocator.h"

constexpr int ALLOCSIZE = 100;
constexpr int ALIGNMENT = 8;

int main()
{
	FreeListAllocator alloc(ALLOCSIZE * (sizeof(int) + 2));
	//StackAllocator alloc(ALLOCSIZE * sizeof(int));

	const int numAllocs = 100;
	int* ptrArray[numAllocs];
	for (int i = 0; i < numAllocs; ++i)
	{
		ptrArray[i] = static_cast<int*>(alloc.Allocate(1 * sizeof(int), ALIGNMENT));
		if (ptrArray[i])
		{
			memset(ptrArray[i], i+1, 1 * sizeof(int));
		}
 	}
	for (int i = 0; i < numAllocs; ++i)
	{
		alloc.Deallocate(ptrArray[i]);
	}
	return 0;
}