#include "allocator.h"
#include <windows.h>


Allocator::Allocator(size_t size) : allocSize(size), offset(0), num_allocations(0)
{
	//start = malloc(allocSize);
	start = VirtualAlloc((void *)(2ull*1024ull*1024ull*1024ull*1024ull), size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

}

size_t Allocator::GetAlignmentPadding(size_t address, uint8_t alignment)
{
	const uint8_t padding = alignment - (address & static_cast<size_t>(alignment - 1));
	if (padding == alignment) return 0;
	return padding;
}

size_t Allocator::GetAlignmentPaddingHeader(size_t address, uint8_t alignment, uint8_t headerSize)
{
	size_t padding = GetAlignmentPadding(address, alignment);
	size_t neededSpace = headerSize;

	if (padding < neededSpace)
	{
		neededSpace -= padding; //Use padding space as header space
		padding += alignment * (neededSpace / alignment); //How many extra padding steps are needed
		if (neededSpace % alignment > 0) padding += alignment; //Make sure adress after header is aligned
	}
	
	return padding;
}

void* Allocator::GetNextAlignedAddress(void* address, uint8_t alignment)
{
	//Beast. Mask off the log2(n) least significant bits
	return  reinterpret_cast<void*>((reinterpret_cast<size_t>(address) + 
		static_cast<uint8_t>(alignment - 1)) & static_cast<uint8_t>(~(alignment - 1)));
}
