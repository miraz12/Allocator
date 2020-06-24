#ifndef _FREE_LIST_ALLOCATOR_H_
#define _FREE_LIST_ALLOCATOR_H_
#include "allocator.h"
#include "linkedlist.h"

class FreeListAllocator : public Allocator
{
private:
	struct FreeHeader
	{
		size_t blockSize;
	};
	struct AllocationHeader
	{
		size_t blockSize;
		size_t padding;
	};

	typedef LinkedList<FreeHeader>::Node Node;

	LinkedList<FreeHeader> freeList;

public:
	FreeListAllocator(size_t size);


	void* Allocate(size_t size, uint8_t alignment) override;
	void Deallocate(void* ptr) override;

	void Find(size_t size, uint8_t alignment, size_t& padding, Node*& pNode, Node*& fNode);
};

#endif //_FREE_LIST_ALLOCATOR_H_
