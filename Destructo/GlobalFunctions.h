#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <new> 
#include <string>

#include "SBitmap.h"

SBitmap LoadBitmapAndAddAlpha(std::string a_path);

float LinearRemap(float a_value, float a_inMin, float a_inMax, float a_outMin, float a_outMax);

template<typename T> void SafeRelease(T* a_interface)
{
    if (a_interface != nullptr)
    {
        a_interface->Release();
        a_interface = nullptr;
    }
}

template<typename T> void SafeDelete(T* a_interface)
{
    if (a_interface != nullptr)
    {
        delete a_interface;
        a_interface = nullptr;
    }
}

//void* operator new (size_t a_size);
//void operator delete (void* a_pData);