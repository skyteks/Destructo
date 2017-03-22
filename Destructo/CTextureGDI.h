#pragma once

#include "ITexture.h"

class CTextureGDI : public ITexture
{
public:
	CTextureGDI(char* a_path);

	~CTextureGDI();

	int GetWidth();

	int GetHeight();

	HBITMAP GetBitmapHandle();

	HDC GetBitmapDeviceContect();

private:

	int x2;
	int y2;
	int m_pitch;
	int m_bitsPerPixel;
	bool m_isLocked;

	UINT* m_data = nullptr;
	HBITMAP bitmapHandle;
	HDC m_bitmapDC;
};

