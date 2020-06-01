#ifndef _LINEAR_ALLOCATOR_H_
#define _LINEAR_ALLOCATOR_H_
#include "allocator.h"

class LinearAllocator : public Allocator
{
public:
	virtual void* Allocate(size_t size, uint8_t alignment = 4) override;
	virtual void Deallocate(void* ptr) override;

protected:
	

	
};

#endif //_ALLOCATOR_H_
