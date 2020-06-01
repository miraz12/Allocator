#include "linearallocator.h"

void* LinearAllocator::Allocate(size_t size, uint8_t alignment)
{
	size_t padding = 0;
	size_t paddedAddress = 0;

	const size_t currentAddress = (size_t)start + offset;

	//Check if aligning is needed
	if (alignment != 0 && offset % alignment != 0)
	{
		padding = CalculatePadding(currentAddress, alignment);
	}

	if (padding + offset + size > allocSize)
		return nullptr;

	offset += padding;
	size_t returnAdress = currentAddress + padding;
	offset += size;

	num_allocations++;
	
	return (void*)returnAdress;
}

void LinearAllocator::Deallocate(void* ptr)
{
}
