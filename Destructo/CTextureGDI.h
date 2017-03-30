#pragma once

#include "ITexture.h"

class CTextureGDI : public ITexture
{
public:
	CTextureGDI(const char* a_path);

	~CTextureGDI();

	int GetWidth();

	int GetHeight();

	int GetPitch();

	int GetBPP();

	void SetPixel(int a_x, int a_y, int a_color);

	HBITMAP GetBitmapHandle();

	HDC GetBitmapDeviceContect();

private:

	int m_width;
	int m_height;
	int m_pitch;
	int m_bitsPerPixel;
	bool m_isLocked;

	UINT* m_data = nullptr;
	HBITMAP m_bitmapHandle;
	HDC m_bitmapDC;
};

