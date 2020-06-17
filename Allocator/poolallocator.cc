#include "poolallocator.h"


PoolAllocator::PoolAllocator(uint8_t alignment, size_t blockSize, size_t size) : Allocator(size)
{
	assert(sizeof(blockSize) <= sizeof(void*));

	int numBlocks = size / blockSize; 
	for (size_t i = 0; i < numBlocks; i++)
	{
		size_t addr = start + i * blockSize;
		blockList.Push(reinterpret_cast<Node*>(addr));
	}

}

void* PoolAllocator::Allocate(size_t size, uint8_t alignment)
{
	Node* newNode = blockList.Pop();
	assert(newNode != nullptr);

	return (void*)newNode;
}

void PoolAllocator::Deallocate(void* ptr)
{
	blockList.Push(static_cast<Node*>(ptr));
}
