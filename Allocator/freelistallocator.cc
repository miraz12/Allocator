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
	Node* newNode;
	Node* previousNode;
	this->Find(size, alignment, padding, previousNode, newNode);
	
	const size_t alignmentPadding = padding - allocationHeaderSize;
	const size_t requiredSize = size + padding;
	const size_t rest = newNode->data.blockSize - requiredSize;

	if (rest > 0) 
	{
		// We have to split the block into the data block and a free block of size 'rest'
		Node* newFreeNode = reinterpret_cast<Node*>(reinterpret_cast<size_t>(newNode) + requiredSize);
		newFreeNode->data.blockSize = rest;
		freeList.Insert(newFreeNode, newNode);
	}
	freeList.Remove(newNode, previousNode);

	// Setup data block
	const size_t headerAddress = reinterpret_cast<size_t>(newNode) + alignmentPadding;
	const size_t dataAddress = headerAddress + allocationHeaderSize;
	reinterpret_cast<AllocationHeader*>(headerAddress)->blockSize = requiredSize;
	reinterpret_cast<AllocationHeader*>(headerAddress)->padding = alignmentPadding;

	num_allocations++;

	return reinterpret_cast<void*>(dataAddress);
}

void FreeListAllocator::Deallocate(void* ptr)
{
	size_t currentAddr = reinterpret_cast<size_t>(ptr);
	size_t headerAddr =  currentAddr - sizeof(AllocationHeader);

	AllocationHeader* allocHeader = reinterpret_cast<AllocationHeader*> (headerAddr);

	Node* freeNode = reinterpret_cast<Node*>(headerAddr);
	freeNode->data.blockSize = allocHeader->blockSize + allocHeader->padding;
	freeNode->next = nullptr;
	
	Node* it = freeList.head;
	Node* itPrev = nullptr;
	while (it != nullptr)
	{
		if (ptr < it) //Sort linked list by address
		{
			freeList.Insert(freeNode, itPrev);
			break;
		}
		itPrev = it;
		it = it->next;
	}

	num_allocations--;
	Coalescence(freeNode, itPrev);
}

void FreeListAllocator::Find(size_t size, uint8_t alignment, size_t& padding, Node*& pNode, Node*& fNode)
{
	Node* it = freeList.head;
	Node* itPrev = nullptr;

	while (it != nullptr) 
	{
		padding = GetAlignmentPaddingHeader(reinterpret_cast<size_t>(it), alignment, sizeof(AllocationHeader));
		size_t requiredSpace = size + padding;
		if (it->data.blockSize >= requiredSpace) 
		{
			break;
		}
		itPrev = it;
		it = it->next;
	}
	pNode = itPrev;
	fNode = it;
	assert(fNode != nullptr && "No block big enough found!");
}

void FreeListAllocator::Coalescence(Node* fNode, Node* pNode)
{
	if (fNode->next != nullptr && reinterpret_cast<size_t>(fNode) + fNode->data.blockSize == reinterpret_cast<size_t>(fNode->next)) 
	{
		fNode->data.blockSize += fNode->next->data.blockSize;
		freeList.Remove(fNode->next, fNode);
	}

	if (pNode != nullptr &&	reinterpret_cast<size_t>(pNode) + pNode->data.blockSize == reinterpret_cast<size_t>(fNode)) 
	{
		pNode->data.blockSize += fNode->data.blockSize;
		freeList.Remove(fNode, pNode);
	}
}
