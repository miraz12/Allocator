#include "linearallocator.h"

void* LinearAllocator::Allocate(size_t size, uint8_t alignment)
{
	size_t padding = 0;
	const size_t currentAddress = (size_t)start + offset;

	void* returnAddr = nullptr;
	//Check if aligning is needed
	padding = GetAlignmentPadding(currentAddress, alignment);

	if (padding + offset + size > allocSize)
		return nullptr;


	returnAddr = (void*)(currentAddress + padding);
	offset += size + padding;
	num_allocations++;
	
	return returnAddr;
}

void LinearAllocator::Deallocate(void* ptr)
{
	this->offset = 0;
	this->num_allocations = 0;
}
