#pragma once
class CFrameAllocator
{
public:
	CFrameAllocator(char* beginning, size_t memorySize);

	~CFrameAllocator();

	char* Allocate(size_t size);

	void Reset();
private:
	char* allocationBeginning;
	size_t allocatedSize;
	char* currentPosition;
};

