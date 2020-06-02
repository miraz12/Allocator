#ifndef _STACK_ALLOCATOR_H_
#define _STACK_ALLOCATOR_H_
#include "allocator.h"

class StackAllocator : public Allocator
{
public:

	StackAllocator(size_t size) : Allocator(size), prevAdress(nullptr), currentAdress(nullptr) {};
	void* Allocate(size_t size, uint8_t alignment = 4) override;
	void Deallocate() override;

private:
	struct header
	{
#if _DEBUG 
		void* prevAdress;
#endif 

		size_t padding;
	};

#if _DEBUG 
	void* prevAdress;
#endif 

	void* currentAdress;
	
};

#endif //_STACK_ALLOCATOR_H_
