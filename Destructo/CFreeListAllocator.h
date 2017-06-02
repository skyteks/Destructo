#pragma once
#include <stdint.h>

struct SFreeListHeader
{
	uint32_t inUse : 1;
	uint32_t size : 31;
};

class CFreeListAllocator
{
public:
	CFreeListAllocator(char* beginning, size_t memorySize);

	~CFreeListAllocator();

	char* Allocate(size_t contentSize);

	void Deallocate(char* chunk);

	size_t GetBiggestFreeChunk() const;
private:
	char* allocationBeginning;
	size_t allocatedSize;

	SFreeListHeader* firstHeader;
};

