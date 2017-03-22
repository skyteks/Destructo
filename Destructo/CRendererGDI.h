#pragma once

#include "IRenderer.h"
#include "CTextureGDI.h"
#include "SRect.h"
#include <wingdi.h>

#pragma comment(lib, "msimg32.lib")

class CRendererGDI : public IRenderer
{
public:
	CRendererGDI();

	~CRendererGDI();

	bool Initialize(HWND a_hwnd);

	ITexture* LoadTextureFromFile(char* a_path);

	void Begin();

	void DrawTexture(int a_posX, int a_posY, int a_width, int a_height, ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight);

	//void MakeCircleInTexture(int a_posX, int a_posY, CTextureGDI* a_texture, int a_color, int a_radius);

	void DrawString(int a_posX, int a_posY, const char* a_string, int a_textColor, int a_backgroundColor, UINT a_format, ITexture* a_fontTexture);

	void End();

	void Shutdown();

private:

	HWND m_windowHandle;
	HDC m_windowDC;
	int m_windowWidth;
	int m_windowHeight;

	HBITMAP m_backBufferBitmap;
	HDC m_backbufferDC;
};

