#include "stackallocator.h"

void* StackAllocator::Allocate(size_t size, uint8_t alignment)
{
	currentAddress = (void*)((size_t)start + offset);
	size_t padding = GetAlignmentPaddingHeader((size_t)currentAddress, alignment, sizeof(header));

	if (padding + offset + size > allocSize)
		return nullptr;

	void* returnAddress = reinterpret_cast<void*>(reinterpret_cast<size_t>(currentAddress) + padding);
	header* head = reinterpret_cast<header*>(reinterpret_cast<size_t>(returnAddress) - sizeof(header));
	head->padding = padding;


	offset += size + padding;
	num_allocations++;
	return  returnAddress;
}

void StackAllocator::Deallocate(void* ptr)
{
	header* head = reinterpret_cast<header*>(reinterpret_cast<size_t>(ptr) - sizeof(header));
	offset = (size_t)ptr - head->padding - (size_t)start;
	num_allocations--;
}
