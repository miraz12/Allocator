#ifndef _POOL_ALLOCATOR_H_
#define _POOL_ALLOCATOR_H_
#include "allocator.h"
#include "stacklinkedlist.h"

class PoolAllocator : public Allocator
{
public:

	PoolAllocator(uint8_t alignment, size_t blockSize, size_t size);
	void* Allocate(size_t size, uint8_t alignment = 4) override;
	void Deallocate(void* ptr) override;

private:
	struct  FreeHeader {};
	using Node = StackLinkedList<FreeHeader>::Node;
	StackLinkedList<FreeHeader> blockList{nullptr};

};

#endif //_POOL_ALLOCATOR_H_
