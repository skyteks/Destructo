#pragma once

#pragma pack(push,1)
struct SBitmapHeader
{
	unsigned short m_signature;
	int m_size;
	unsigned short m_reserved0;
	unsigned short m_reserved1;
	unsigned int m_imageDataOffset;
	unsigned int m_structSize;
	int m_width;
	int m_height;
	unsigned short m_numPlanes;
	unsigned short m_bitsPerPixel;
	unsigned int m_compression;
	unsigned int m_sizeOfImageData;
	int m_horizontalResolution;
	int m_verticalResolution;
	unsigned int m_numColorsInImage;
	unsigned int m_numColorsImportant;
};
#pragma pack(pop)