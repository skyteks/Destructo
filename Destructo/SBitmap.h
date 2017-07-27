#pragma once

#include "SBitmapHeader.h"

#pragma pack(push,1)
struct SBitmap
{
    SBitmapHeader m_header;
    int m_pitch;
    unsigned char* m_data;
};
#pragma pack(pop)