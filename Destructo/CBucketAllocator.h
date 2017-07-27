#pragma once

class CBucketAllocator
{
public:
    CBucketAllocator(size_t oneBucketSize, char* beginning, size_t memorySize);

    ~CBucketAllocator();

    char* Allocate();

    void Deallocate(char* bucket);

    size_t GetFreeSize() const;
private:
    char* allocationBeginning;
    char* bucketsBeginning;
    size_t allocatedSize;
    size_t bucketSize;
    size_t totalBuckets;

    bool* occupiedBuckets;
};

