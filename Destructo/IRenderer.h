#pragma once

#include <Windows.h>
#include <string>
#include "ITexture.h"
#include "ERenderer.h"

class CGameObject;

class IRenderer
{
public:

    IRenderer() {}

    virtual ~IRenderer() {}

    virtual bool Initialize(HWND a_hwnd) = 0;

    virtual ITexture* LoadTextureFromFile(std::string a_path) = 0;

    virtual void Begin() = 0;

    virtual void DrawObject(CGameObject& a_gameObject) = 0;

    virtual void DrawTexture(int a_posX, int a_posY, int a_width, int a_height, const ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight) = 0;

    virtual void DrawTextureWithOpacityMask(int a_posX, int a_posY, int a_width, int a_height, const ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight, const ITexture* a_opacityMask) = 0;

    virtual void DrawString(int a_posX, int a_posY, const char* a_string, int a_textColor, int a_backgroundColor, UINT a_format, const ITexture* a_fontTexture) = 0;

    virtual void End() = 0;

    virtual void Shutdown() = 0;

    virtual ERenderer GetRendererType() = 0;
};