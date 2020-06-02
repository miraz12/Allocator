#include "stackallocator.h"

void* StackAllocator::Allocate(size_t size, uint8_t alignment)
{
	size_t padding = GetAlignmentPaddingHeader(size, alignment, sizeof(header));

	if (padding + offset + size > allocSize)
		return nullptr;

	void* returnAddress = reinterpret_cast<void*>(reinterpret_cast<size_t>(currentAdress) + padding);
	header* head = reinterpret_cast<header*>(reinterpret_cast<size_t>(returnAddress) - padding);
	head->padding = padding;
#if _DEBUG 
	head->prevAdress = prevAdress;
	prevAdress = returnAddress;
#endif

	currentAdress = reinterpret_cast<void*>(reinterpret_cast<size_t>(returnAddress) + size);
	num_allocations++;
	return  nullptr;
}

void StackAllocator::Deallocate()
{
}
