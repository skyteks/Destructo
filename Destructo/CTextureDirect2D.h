#pragma once



#pragma comment(lib, "Windowscodecs.lib")

#include "GlobalFunctions.h"

//#include <d2d1_1.h>

#include <d2d1.h>
#include <Wincodec.h>

#include "ITexture.h"



class CTextureDirect2D : public ITexture
{
public:
	
	CTextureDirect2D(const char* a_path);

	~CTextureDirect2D() override;

	int GetWidth() override;

	int GetHeight() override;

	int GetPitch() override;

	int GetBPP() override;

	void SetPixel(int a_x, int a_y, int a_color) override;

	ID2D1Bitmap* GetBitmapHandle();

	static ID2D1HwndRenderTarget* s_renderTarget;

private:
	int m_width;
	int m_height;
	int m_pitch;
	int m_bitsPerPixel;
	bool m_isLocked;
	char* m_name;

	ID2D1Bitmap *m_bitmap = nullptr;
};


