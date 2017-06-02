#pragma once

#pragma comment(lib, "Windowscodecs.lib")

#include "GlobalFunctions.h"

#include <d2d1.h>
#include <Wincodec.h>

#include "ITexture.h"
#include <string>


class CTextureDirect2D : public ITexture
{
public:
	
	CTextureDirect2D(std::string a_path);

	~CTextureDirect2D() override;

	int GetWidth() const override;

	int GetHeight() const override;

	int GetPitch() const override;

	int GetBPP() const override;

	void SetPixel(int a_x, int a_y, int a_color) override;

	ID2D1Bitmap* GetBitmapHandle() const;

	static ID2D1HwndRenderTarget* s_renderTarget;

private:
	int m_width;
	int m_height;
	int m_pitch;
	int m_bitsPerPixel;
	bool m_isLocked;

	mutable ID2D1Bitmap* m_bitmap = nullptr;
};


