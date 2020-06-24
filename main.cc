#include "Allocator/linearallocator.h"
#include "Allocator/stackallocator.h"
#include "Allocator/poolallocator.h"
#include "Allocator/freelistallocator.h"

constexpr int ALLOCSIZE = 100;
constexpr int ALIGNMENT = 8;

int main()
{
	FreeListAllocator alloc(ALLOCSIZE * sizeof(int));
	//StackAllocator alloc(ALLOCSIZE * sizeof(int));

	for (int i = 0; i < 10; ++i)
	{
		int* ptr = static_cast<int*>(alloc.Allocate(10 * sizeof(int), ALIGNMENT));
		if (ptr)
		{
			memset(ptr, i+1, 10 * sizeof(int));
		}
 	}

	return 0;
}