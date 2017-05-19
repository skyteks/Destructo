#pragma once

#include "ITexture.h"
#include <string>

class CTextureGDI : public ITexture
{
public:
	CTextureGDI(std::string a_path);

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

	UINT* m_data = nullptr;
	HBITMAP m_bitmapHandle;
	HDC m_bitmapDC;
};

