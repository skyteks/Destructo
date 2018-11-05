#include "SBitmap.h"
#include <malloc.h>

void SBitmap::FreeData()
{
    if (m_data != nullptr)
    {
        free(m_data);
        m_data = nullptr;
    }
}
