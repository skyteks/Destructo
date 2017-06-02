#include "CFreeListAllocator.h"

#include <exception>

CFreeListAllocator::CFreeListAllocator(char* beginning, size_t memorySize)
{
	if (beginning == nullptr || memorySize <= 0)
		throw std::exception();

	allocationBeginning = beginning;
	allocatedSize = memorySize;

	firstHeader = reinterpret_cast<SFreeListHeader*>(beginning);
	firstHeader->inUse = false;
	firstHeader->size = allocatedSize - sizeof(SFreeListHeader);
}


CFreeListAllocator::~CFreeListAllocator()
{
	allocationBeginning = nullptr;
	allocatedSize = 0;
}

char* CFreeListAllocator::Allocate(size_t contentSize)
{
	SFreeListHeader* header = firstHeader;
	while (header->inUse || header->size < contentSize + sizeof(SFreeListHeader))
	{
		header = reinterpret_cast<SFreeListHeader*>(reinterpret_cast<char*>(header) + header->size);

		if (reinterpret_cast<char*>(header) >= allocationBeginning + allocatedSize)
		{
			return nullptr;
		}
	}

	header->inUse = true;
	size_t oldHeaderSize = header->size;
	header->size = contentSize;
	char* chunk = reinterpret_cast<char*>(header) + sizeof(SFreeListHeader);

	SFreeListHeader* nextHeader = reinterpret_cast<SFreeListHeader*>(reinterpret_cast<char*>(header) + header->size);
	nextHeader->inUse = false;
	nextHeader->size = oldHeaderSize - (contentSize + sizeof(SFreeListHeader));

	return chunk;
}

void CFreeListAllocator::Deallocate(char* chunk)
{
	SFreeListHeader* chunkHeader = reinterpret_cast<SFreeListHeader*>(chunk);
	SFreeListHeader* header = firstHeader;
	do
	{
		SFreeListHeader* lastHeader = header;
		SFreeListHeader* nextHeader = reinterpret_cast<SFreeListHeader*>(reinterpret_cast<char*>(header) + header->size);
		header = nextHeader;

		if (reinterpret_cast<char*>(header) >= allocationBeginning + allocatedSize)
		{
			return;
		}

		if (header == chunkHeader)
		{
			header->inUse = false;
			if (!nextHeader->inUse)
			{
				header->size += nextHeader->size + sizeof(SFreeListHeader);
			}
			if (!lastHeader->inUse)
			{
				lastHeader->size += header->size + sizeof(SFreeListHeader);
			}
			return;
		}
	} while (header->inUse);
}

size_t CFreeListAllocator::GetBiggestFreeChunk() const
{
	size_t chunkSize = 0;
	SFreeListHeader* header = firstHeader;
	do
	{
		if (header->size > chunkSize)
		{
			chunkSize = header->size;
		}
		header = reinterpret_cast<SFreeListHeader*>(reinterpret_cast<char*>(header) + header->size);
	} while (reinterpret_cast<char*>(header) < allocationBeginning + allocatedSize);
	return chunkSize;
}


