#ifndef _LINEAR_ALLOCATOR_H_
#define _LINEAR_ALLOCATOR_H_
#include "allocator.h"

class LinearAllocator : public Allocator
{
public:

	LinearAllocator(size_t size) : Allocator(size) {};
	void* Allocate(size_t size, uint8_t alignment = 4) override;
	void Deallocate(void* ptr) override;
	
};

#endif //_LINEAR_ALLOCATOR_H_
