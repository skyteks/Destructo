#include "GlobalFunctions.h"

SBitmap LoadBitmapAndAddAlpha(std::string a_path)
{
    FILE* file;
    fopen_s(&file, a_path.c_str(), "rb");

    SBitmap bmp;

    fread(&bmp.m_header, sizeof(SBitmapHeader), 1, file);

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    bmp.m_header.m_sizeOfImageData = length - bmp.m_header.m_imageDataOffset;
    fseek(file, bmp.m_header.m_imageDataOffset, SEEK_SET);

    bmp.m_data = reinterpret_cast<unsigned char*>(malloc(bmp.m_header.m_sizeOfImageData));

    fread(bmp.m_data, bmp.m_header.m_sizeOfImageData, 1, file);

    fclose(file);

    bmp.m_pitch = bmp.m_header.m_width * 3;

    if (bmp.m_pitch % 4 != 0)
    {
        bmp.m_pitch += 4 - (bmp.m_pitch % 4);
    }

    bmp.m_pitch -= (bmp.m_header.m_width * 3);

    unsigned char* buffer = reinterpret_cast<unsigned char*>(malloc(bmp.m_header.m_sizeOfImageData * 4 / 3));

    size_t i = 0;
    uint32_t j = 0;
    while (i < bmp.m_header.m_sizeOfImageData)
    {
        unsigned char r = bmp.m_data[i + 2];
        unsigned char g = bmp.m_data[i + 1];
        unsigned char b = bmp.m_data[i];

        buffer[j++] = bmp.m_data[i++ + 2];
        buffer[j++] = bmp.m_data[i++];
        buffer[j++] = bmp.m_data[i++ - 2];

        if (r == 255 && g == 0 && b == 255)
            buffer[j++] = 0;
        else
            buffer[j++] = 255;
    }

    bmp.m_header.m_bitsPerPixel = 32;
    bmp.m_header.m_sizeOfImageData = bmp.m_header.m_sizeOfImageData * 4 / 3;
    bmp.m_header.m_size = bmp.m_header.m_sizeOfImageData + sizeof(SBitmapHeader);

    bmp.FreeData();

    bmp.m_data = buffer;

    return bmp;
}


float LinearRemap(float a_value, float a_inMin, float a_inMax, float a_outMin, float a_outMax)
{
    return (a_value - a_inMin) * (a_outMax - a_outMin) / (a_inMax - a_inMin) + a_outMin;
}


int LinearRemap(int a_value, int a_inMin, int a_inMax, int a_outMin, int a_outMax)
{
    return (a_value - a_inMin) * (a_outMax - a_outMin) / (a_inMax - a_inMin) + a_outMin;
}

/*
static size_t newCounter = 0;
static size_t memoryLeaksCounter = 0;
#include <map>
#include <Windows.h>
#include <WinBase.h>

static std::map<WORD, long long> callstack;
static bool firstNew = true;

void NewDeleteLeaks()
{

    //leakdetektor
    //valgrind

    printf("New Allocations: %u, MemoryLeaks: %u\n", newCounter, memoryLeaksCounter);
}

void* operator new (size_t a_size)
{
    //system backtrace (callstack holen, hinter new adresse speichern)
    newCounter++;
    memoryLeaksCounter++;
    if (firstNew)
    {
        firstNew = false;
        atexit(NewDeleteLeaks);
        //callstack = std::map<WORD, long long>();
    }
    void* var = malloc(a_size);
    //WORD key = CaptureStackBackTrace(1, 20, &var, nullptr);
    //callstack.insert(std::pair<WORD, long long>(key, reinterpret_cast<long long>(var)));
    return var;
}
void operator delete (void* a_pData)
{
    memoryLeaksCounter--;
    if (a_pData != nullptr)
    {
        free(a_pData);
    }
}
*/