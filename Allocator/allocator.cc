#include "allocator.h"
#include <stdlib.h>


Allocator::Allocator(size_t size) : allocSize(size), offset(0), num_allocations(0)
{
	start = malloc(allocSize);
}

size_t Allocator::GetAlignmentPadding(size_t address, uint8_t alignment)
{
	const uint8_t padding = alignment - (address & static_cast<size_t>(alignment - 1));
	if (padding == alignment) return 0;
	return padding;
}

size_t Allocator::GetAlignmentPaddingHeader(size_t address, uint8_t alignment, uint8_t headerSize)
{
	uint8_t padding = GetAlignmentPadding(address, alignment);
	uint8_t neededSpace = headerSize;

	if (padding < neededSpace)
	{
		neededSpace -= padding;
		padding += padding * (neededSpace / alignment);
		if (neededSpace % alignment > 0) padding += padding;
	}
	
	return padding;
}

void* Allocator::GetNextAlignedAddress(void* address, uint8_t alignment)
{
	//Beast. Mask off the log2(n) least significant bits
	return  reinterpret_cast<void*>((reinterpret_cast<size_t>(address) + 
		static_cast<uint8_t>(alignment - 1)) & static_cast<uint8_t>(~(alignment - 1)));
}
