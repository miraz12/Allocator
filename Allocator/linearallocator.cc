#include "linearallocator.h"

void* LinearAllocator::Allocate(size_t size, uint8_t alignment)
{
	size_t padding = 0;
	size_t currentAddress = (size_t)start + offset;

	void* returnAddr = nullptr;
	//Check if aligning is needed
	padding = GetAlignmentPadding(currentAddress, alignment);

	if (padding + offset + size > allocSize)
		return nullptr;


	returnAddr = (void*)(currentAddress + padding);
	offset += size;
	num_allocations++;
	
	return returnAddr;
}

void LinearAllocator::Deallocate()
{
	this->offset = 0;
	this->num_allocations = 0;
}
