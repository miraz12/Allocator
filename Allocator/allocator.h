#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_
#include <cstdint>
#include <assert.h>

class Allocator
{
public:

	Allocator(size_t size, void* start);
	virtual ~Allocator()
	{
		assert(num_allocations == 0 && offset == 0);
		start = nullptr; allocSize = 0;
	}
	
	virtual void* Allocate(size_t size, uint8_t alignment = 4) = 0;
	virtual void Deallocate(void* ptr) = 0;

protected:
	size_t GetAlignmentPadding(size_t adress, uint8_t alignment);
	void* GetNextAlignedAdress(void* adress, uint8_t alignment);
	
	void* start;
	size_t allocSize;
	size_t offset;
	size_t num_allocations;
};

#endif //_ALLOCATOR_H_
