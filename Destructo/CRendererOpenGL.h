#pragma once

// TODO:
// IObject interface
// GameObject class (position, scale, rotation, ITexture*)
// DrawObject method for all renderers
// DrawOpacity method for all renderers

#include "IRenderer.h"
#include "CTextureOpenGL.h"
#include <gl\GL.h>
#include "SRect.h"
#include "SMatrix4x4.h"
#include "CTextureManager.h"
#include "DataNames.h"
#pragma comment(lib, "opengl32.lib")

class CRendererOpenGL : public IRenderer
{
public:
    CRendererOpenGL();

    ~CRendererOpenGL() override;

    bool Initialize(HWND a_hwnd) override;

    ITexture* LoadTextureFromFile(std::string a_path) override;

    void Begin() override;

    void DrawObject(CGameObject& a_gameObject) override;

    void DrawTexture(int a_posX, int a_posY, int a_width, int a_height, const ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight) override;

    void DrawTextureWithOpacityMask(int a_posX, int a_posY, int a_width, int a_height, const ITexture * a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight, const ITexture * a_opacityMask) override;

    void DrawString(int a_posX, int a_posY, const char* a_string, int a_textColor, int a_backgroundColor, UINT a_format, const ITexture* a_fontTexture) override;

    void End() override;

    void Shutdown() override;

private:
    HWND m_windowHandle;
    HDC m_windowDC;
    int m_windowWidth;
    int m_windowHeight;

    ITexture* m_fontTexture = nullptr;
};

