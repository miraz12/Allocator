#include "freelistallocator.h"

FreeListAllocator::FreeListAllocator(size_t size) : Allocator(size)
{
	Node * firstNode = (Node *)start;
	firstNode->data.blockSize = size;
	firstNode->next = nullptr;
	freeList.head = nullptr;
	freeList.Insert(firstNode, nullptr);
}

void* FreeListAllocator::Allocate(size_t size, uint8_t alignment)
{
	const size_t allocationHeaderSize = sizeof(AllocationHeader);

	// Search through the free list for a free block that has enough space to allocate our data
	size_t padding;
	Node * affectedNode,
		*previousNode;
	this->Find(size, alignment, padding, previousNode, affectedNode);


	const size_t alignmentPadding = padding - allocationHeaderSize;
	const size_t requiredSize = size + padding;

	const size_t rest = affectedNode->data.blockSize - requiredSize;

	if (rest > 0) {
		// We have to split the block into the data block and a free block of size 'rest'
		Node * newFreeNode = (Node *)((size_t) affectedNode + requiredSize);
		newFreeNode->data.blockSize = rest;
		freeList.Insert(newFreeNode, affectedNode);
	}
	freeList.Remove(affectedNode, previousNode);

	// Setup data block
	const size_t headerAddress = (size_t) affectedNode + alignmentPadding;
	const size_t dataAddress = headerAddress + allocationHeaderSize;
	((AllocationHeader *) headerAddress)->blockSize = requiredSize;
	((AllocationHeader *) headerAddress)->padding = alignmentPadding;

	//m_used += requiredSize;
	//m_peak = std::max(m_peak, m_used);

	return (void*)dataAddress;
}

void FreeListAllocator::Deallocate(void* ptr)
{
}

void FreeListAllocator::Find(size_t size, uint8_t alignment, size_t& padding, Node*& pNode, Node*& fNode)
{
	Node* it = freeList.head;
	Node* itPrev = nullptr;

	while (it != nullptr) 
	{
		padding = GetAlignmentPaddingHeader(reinterpret_cast<size_t>(it), alignment, sizeof(AllocationHeader));
		const size_t requiredSpace = size + padding;
		if (it->data.blockSize >= requiredSpace) 
		{
			break;
		}
		itPrev = it;
		it = it->next;
	}
	pNode = itPrev;
	fNode = it;
}
