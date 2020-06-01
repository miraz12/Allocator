#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_
#include <cstdint>
#include <assert.h>

class Allocator
{
public:

	Allocator(size_t size, void* start) : start(start), allocSize(size), offset(0), num_allocations(0) {}
	virtual ~Allocator()
	{
		assert(num_allocations == 0 && offset == 0);
		start = nullptr; allocSize = 0;
	}
	
	virtual void* Allocate(size_t size, uint8_t alignment = 4) = 0;
	virtual void Deallocate(void* ptr) = 0;

protected:

	uint8_t alignForwardAdjustment(size_t address, uint8_t alignment)
	{
		const size_t multiplier = (address / alignment) + 1;
		const size_t alignedAddress = multiplier * alignment;
		const size_t padding = alignedAddress - address;
		return padding;
	}
	
	void* start;
	size_t allocSize;
	size_t offset;
	size_t num_allocations;
};

#endif //_ALLOCATOR_H_
