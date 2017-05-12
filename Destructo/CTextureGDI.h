#pragma once

#include "ITexture.h"

class CTextureGDI : public ITexture
{
public:
	CTextureGDI(const char* a_path);

	~CTextureGDI() override;

	int GetWidth() override;

	int GetHeight() override;

	int GetPitch() override;

	int GetBPP() override;

	void SetPixel(int a_x, int a_y, int a_color) override;

	HBITMAP GetBitmapHandle();

	HDC GetBitmapDeviceContect();

private:

	int m_width;
	int m_height;
	int m_pitch;
	int m_bitsPerPixel;
	bool m_isLocked;
	char* m_name;

	UINT* m_data = nullptr;
	HBITMAP m_bitmapHandle;
	HDC m_bitmapDC;
};

