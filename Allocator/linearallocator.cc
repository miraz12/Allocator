#include "linearallocator.h"

void* LinearAllocator::Allocate(size_t size, uint8_t alignment)
{
	size_t padding = 0;
	size_t paddedAddress = 0;

	size_t currentAddress = (size_t)start + offset;

	void* returnAddr = nullptr;
	//Check if aligning is needed
	if (alignment != 0 && offset % alignment != 0)
	{
		padding = GetAlignmentPadding(currentAddress, alignment);
		//returnAddr = GetNextAlignedAdress(currentAddress, alignment);
	}

	if (padding + offset + size > allocSize)
		return nullptr;

	offset += padding;
	returnAddr = (void*)(currentAddress + offset);
	offset += size;

	num_allocations++;
	
	return returnAddr;
}

void LinearAllocator::Deallocate(void* ptr)
{
	this->offset = 0;
	this->num_allocations = 0;
}
