#include "CBucketAllocator.h"

#include <exception>
#include <array>

CBucketAllocator::CBucketAllocator(size_t oneBucketSize, char* beginning, size_t memorySize)
{
    if (oneBucketSize <= 0 || beginning == nullptr || memorySize <= 0 || oneBucketSize + sizeof(bool) >= memorySize)
    {
        throw std::exception();
    }

    bucketSize = oneBucketSize;
    allocationBeginning = beginning;
    allocatedSize = memorySize;

    totalBuckets = allocatedSize / bucketSize;
    size_t rest = allocatedSize % bucketSize;

    size_t overheadStructureSize = totalBuckets * sizeof(bool);

    size_t usedSize = allocatedSize - overheadStructureSize;

    totalBuckets = usedSize / bucketSize;

    bucketsBeginning = allocationBeginning + overheadStructureSize;
    occupiedBuckets = reinterpret_cast<bool*>(allocationBeginning);
    memset(occupiedBuckets, false, totalBuckets);
}


CBucketAllocator::~CBucketAllocator()
{
    allocationBeginning = nullptr;
    allocatedSize = 0;
    bucketSize = 0;
    totalBuckets = 0;

    occupiedBuckets = nullptr;
}

char* CBucketAllocator::Allocate()
{
    for (size_t i = 0; i < totalBuckets; i++)
    {
        if (!occupiedBuckets[i])
        {
            occupiedBuckets[i] = true;
            char* bucket = bucketsBeginning + i * bucketSize;
#if DEBUG || _DEBUG
            memset(bucket, 0xCD, bucketSize);
#endif
            return bucket;
        }
    }
    return nullptr;
}

void CBucketAllocator::Deallocate(char* bucket)
{
    if (bucket < bucketsBeginning || bucket > bucketsBeginning + totalBuckets * bucketSize)
    {
        throw std::exception();
    }

    for (size_t i = 0; i < totalBuckets; i++)
    {
        if (bucketsBeginning + i * bucketSize == bucket)
        {
            if (occupiedBuckets[i])
            {
                occupiedBuckets[i] = false;
#if DEBUG || _DEBUG
                memset(bucket, 0xDD, bucketSize);
#endif
                bucket = nullptr;
            }
            else
            {
                throw std::exception();
            }
            return;
        }
    }
    throw std::exception();
}

size_t CBucketAllocator::GetFreeSize() const
{
    size_t freeOnes = 0;
    for (size_t i = 0; i < totalBuckets; i++)
    {
        if (occupiedBuckets[i])
        {
            freeOnes++;
        }
    }
    return freeOnes;
}