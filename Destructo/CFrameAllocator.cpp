#include "CFrameAllocator.h"

#include <new>

CFrameAllocator::CFrameAllocator(char* beginning, size_t memorySize)
{
	if (beginning == nullptr || memorySize <= 0)
		throw std::exception();

	allocationBeginning = beginning;
	allocatedSize = memorySize;
	currentPosition = allocationBeginning;
}

CFrameAllocator::~CFrameAllocator()
{
	allocationBeginning = nullptr;
	allocatedSize = 0;
	currentPosition = nullptr;
}

char* CFrameAllocator::Allocate(size_t size)
{
	if (size <= 0 || currentPosition + size - allocationBeginning > allocatedSize)
	{
		throw std::bad_alloc();
		//return nullptr;
	}

	currentPosition += size;
	return currentPosition;
}

void CFrameAllocator::Reset()
{
	currentPosition = allocationBeginning;
}