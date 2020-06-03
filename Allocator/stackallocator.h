#ifndef _STACK_ALLOCATOR_H_
#define _STACK_ALLOCATOR_H_
#include "allocator.h"

class StackAllocator : public Allocator
{
public:

	StackAllocator(size_t size) : Allocator(size), currentAddress(nullptr) 
	{

	};
	void* Allocate(size_t size, uint8_t alignment = 4) override;
	void Deallocate(void* ptr) override;

private:
	struct header
	{
		size_t padding;
	};

	void* currentAddress;
};

#endif //_STACK_ALLOCATOR_H_
