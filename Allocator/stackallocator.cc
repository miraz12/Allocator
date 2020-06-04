#include "stackallocator.h"

void* StackAllocator::Allocate(size_t size, uint8_t alignment)
{
	size_t currentAddress = (start + offset);
	size_t padding = GetAlignmentPaddingHeader(currentAddress, alignment, sizeof(header));

	if (padding + offset + size > allocSize)
		return nullptr;

	size_t returnAddress = currentAddress + padding;
	header* head = reinterpret_cast<header*>(returnAddress - sizeof(header));
	head->padding = padding;


	offset += size + padding;
	num_allocations++;
	return  reinterpret_cast<void*>(returnAddress);
}

void StackAllocator::Deallocate(void* ptr)
{
	size_t ptrVal = reinterpret_cast<size_t>(ptr);
	header* head = reinterpret_cast<header*>(ptrVal - sizeof(header));
	offset = ptrVal - head->padding - start;
	num_allocations--;
}
