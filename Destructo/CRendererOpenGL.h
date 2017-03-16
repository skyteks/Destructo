#pragma once

#include "IRenderer.h"
#include "CTextureOpenGL.h"
#include <gl\GL.h>
#include "SRect.h"
#pragma comment(lib, "opengl32.lib")

class CRendererOpenGL : public IRenderer
{
public:
	CRendererOpenGL();

	~CRendererOpenGL();

	bool Initialize(HWND a_hwnd);

	ITexture* LoadTextureFromFile(char* a_path);

	void Begin();

	void DrawTexture(int a_posX, int a_posY, int a_width, int a_height, ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight);

	void DrawString(int a_posX, int a_posY, const char* a_string, int a_textColor, int a_backgroundColor, UINT a_format, ITexture* a_fontTexture);

	void End();

	void Shutdown();

private:
	HWND m_windowHandle;
	HDC m_windowDC;
	int m_windowWidth;
	int m_windowHeight;

	ITexture* m_fontTexture = nullptr;
};

