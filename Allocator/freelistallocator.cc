#include "freelistallocator.h"

FreeListAllocator::FreeListAllocator(size_t size, const LinkedList<FreeHeader>& free_list) : Allocator(size)
{

}

void* FreeListAllocator::Allocate(size_t size, uint8_t alignment)
{
	const std::size_t allocationHeaderSize = sizeof(AllocationHeader);
	const std::size_t freeHeaderSize = sizeof(FreeHeader);
}

void FreeListAllocator::Deallocate(void* ptr)
{
}
