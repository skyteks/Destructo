#pragma once

#include <Windows.h>
#include "ITexture.h"
#include "ERenderer.h"

class IRenderer
{
public:

	IRenderer(){}

	virtual ~IRenderer(){}

	virtual bool Initialize(HWND a_hwnd) = 0;

	virtual ITexture* LoadTextureFromFile(const char* a_path) = 0;

	virtual void Begin() = 0;

	virtual void DrawTexture(int a_posX, int a_posY, int a_width, int a_height, ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight) = 0;

	virtual void DrawString(int a_posX, int a_posY, const char* a_string, int a_textColor, int a_backgroundColor, UINT a_format, ITexture* a_fontTexture) = 0;

	virtual void End() = 0;

	virtual void Shutdown() = 0;
};