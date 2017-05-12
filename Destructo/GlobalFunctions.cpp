#include "GlobalFunctions.h"

SBitmap LoadBitmapAndAddAlpha(const char* a_path)
{
	FILE* file;
	fopen_s(&file, a_path, "rb");

	SBitmap bmp;
	
	fread(&bmp.m_header, sizeof(SBitmapHeader), 1, file);

	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);

	bmp.m_header.m_sizeOfImageData = length - bmp.m_header.m_imageDataOffset;
	fseek(file, bmp.m_header.m_imageDataOffset, SEEK_SET);

	bmp.m_data = (unsigned char*)malloc(bmp.m_header.m_sizeOfImageData);

	fread(bmp.m_data, bmp.m_header.m_sizeOfImageData, 1, file);

	fclose(file);

	bmp.m_pitch = bmp.m_header.m_width * 3;

	if (bmp.m_pitch % 4 != 0)
	{
		bmp.m_pitch += 4 - (bmp.m_pitch % 4);
	}

	bmp.m_pitch -= (bmp.m_header.m_width * 3);

	unsigned char* buffer = (unsigned char*)malloc(bmp.m_header.m_sizeOfImageData * 4 / 3);

	int i = 0;
	int j = 0;
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

	free(bmp.m_data);

	bmp.m_data = buffer;

	return bmp;
}


float Map(float a_value, float a_inMin, float a_inMax, float a_outMin, float a_outMax)
{
	return (a_value - a_inMin) * (a_outMax - a_outMin) / (a_inMax - a_inMin) + a_outMin;
}


static unsigned int newDeleteCounter = 0;
static unsigned int newCounter = 0;

void NewDeleteLeaks()
{
	unsigned int tmp = newDeleteCounter;
	unsigned int tmp2 = newCounter;
}

void* operator new (size_t a_size)
{
	atexit(NewDeleteLeaks);
	newDeleteCounter++;
	newCounter++;
	return malloc(a_size);
}
void operator delete (void* a_pData)
{
	newDeleteCounter--;
	if (a_pData != nullptr)
	{
		free(a_pData);
	}
}