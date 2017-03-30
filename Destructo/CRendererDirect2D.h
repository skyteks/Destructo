#pragma once

#pragma comment(lib, "D2d1.lib")
#pragma comment(lib, "Dwrite.lib")
#include "SRect.h"
#include "GlobalFunctions.h"

#include <d2d1.h>
//#include <d2d1_1.h>
#include <dwrite.h>

#include "IRenderer.h"
#include "CTextureDirect2D.h"

class CRendererDirect2D : public IRenderer
{
public:

	CRendererDirect2D();

	~CRendererDirect2D();

	bool Initialize(HWND a_hwnd);

	ITexture* LoadTextureFromFile(const char * a_path);

	void Begin();

	void DrawTexture(int a_posX, int a_posY, int a_width, int a_height, ITexture * a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight);
	
	void DrawString(int a_posX, int a_posY, const char * a_string, int a_textColor, int a_backgroundColor, UINT a_format, ITexture * a_fontTexture);
	
	void End();
	
	void Shutdown();

	D2D1_COLOR_F NewColor(int a_color);

	void Clear(int a_color);

private:

	HWND m_windowHandle;
	HDC m_windowDC;
	int m_windowWidth;
	int m_windowHeight;

	ID2D1Factory* m_imageFactory = nullptr;
	ID2D1HwndRenderTarget* m_renderTarget = nullptr;
	IDWriteFactory* m_writeFactory = nullptr;
	IDWriteTextFormat* m_writeTextFormat = nullptr;

	ID2D1SolidColorBrush* m_colorBrush = nullptr;
	D2D1::ColorF m_clearColor;
	
};

