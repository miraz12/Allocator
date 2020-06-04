#include "linearallocator.h"

void* LinearAllocator::Allocate(size_t size, uint8_t alignment)
{
	const size_t currentAddress = start + offset;

	//Check if aligning is needed
	size_t padding = GetAlignmentPadding(currentAddress, alignment);

	if (padding + offset + size > allocSize)
		return nullptr;

	size_t returnAddr = currentAddress + padding;
	offset += size + padding;
	num_allocations++;
	
	return reinterpret_cast<void*>(returnAddr);
}

void LinearAllocator::Deallocate(void* ptr)
{
	offset = 0;
	num_allocations = 0;
}
 