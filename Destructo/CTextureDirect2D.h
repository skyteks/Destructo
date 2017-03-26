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
	
	CTextureDirect2D(char* a_path);

	~CTextureDirect2D();

	int GetWidth();

	int GetHeight();

	int GetPitch();

	int GetBPP();

	ID2D1Bitmap* GetBitmapHandle();

	static ID2D1HwndRenderTarget* s_renderTarget;

private:
	int x2;
	int y2;
	int m_pitch;
	int m_bitsPerPixel;
	bool m_isLocked;

	ID2D1Bitmap *m_bitmap = nullptr;
};


