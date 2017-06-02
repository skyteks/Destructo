#pragma once

#include <stdint.h>

#pragma pack(push,1)
struct SBitmapHeader
{
	unsigned short m_signature;
	int m_size;
	unsigned short m_reserved0;
	unsigned short m_reserved1;
	uint32_t m_imageDataOffset;
	uint32_t m_structSize;
	int m_width;
	int m_height;
	unsigned short m_numPlanes;
	unsigned short m_bitsPerPixel;
	uint32_t m_compression;
	uint32_t m_sizeOfImageData;
	int m_horizontalResolution;
	int m_verticalResolution;
	uint32_t m_numColorsInImage;
	uint32_t m_numColorsImportant;
};
#pragma pack(pop)