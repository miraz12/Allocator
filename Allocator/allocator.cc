#include "allocator.h"
Allocator::Allocator(size_t size, void* start) : start(start), allocSize(size), offset(0), num_allocations(0)
{

}

size_t Allocator::GetAlignmentPadding(size_t address, uint8_t alignment)
{
	uint8_t adjustment = alignment - (address & static_cast<size_t>(alignment - 1));

	if (adjustment == alignment) return 0;

	return adjustment;
}

void* Allocator::GetNextAlignedAdress(void* address, uint8_t alignment)
{
	return  (void*)((reinterpret_cast<size_t>(address) + static_cast<uint8_t>(alignment - 1)) & static_cast<uint8_t>(~(alignment - 1)));
}
