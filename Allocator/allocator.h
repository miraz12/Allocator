#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_
#include <cstdint>
#include <assert.h>
#include <cstdlib>

class Allocator
{
public:

	Allocator(size_t size);
	virtual ~Allocator()
	{
		assert(num_allocations == 0 && offset == 0);
		start = nullptr; allocSize = 0;
		VirtualFree((void*)start);
	}
	
	virtual void* Allocate(size_t size, uint8_t alignment = 4) = 0;
	virtual void Deallocate(void* ptr) = 0;

protected:
	size_t GetAlignmentPadding(size_t address, uint8_t alignment);
	size_t GetAlignmentPaddingHeader(size_t address, uint8_t alignment, uint8_t headerSize);
	void* GetNextAlignedAddress(void* address, uint8_t alignment);
	
	size_t start;
	size_t allocSize;
	size_t offset;
	size_t num_allocations;
};

#endif //_ALLOCATOR_H_
