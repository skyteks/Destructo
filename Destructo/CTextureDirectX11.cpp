#include "CTextureDirectX11.h"

CTextureDirectX11::CTextureDirectX11(ID3D11Texture2D* a_texture, ID3D11ShaderResourceView* a_shaderResView)
{
    m_texture = a_texture;
    D3D11_TEXTURE2D_DESC textureDesc;
    m_texture->GetDesc(&textureDesc);
    m_width = textureDesc.Width;
    m_height = textureDesc.Height;

    m_shaderResourceView = a_shaderResView;
}


CTextureDirectX11::~CTextureDirectX11()
{
    SafeRelease(m_texture);
    SafeRelease(m_shaderResourceView);
}

int CTextureDirectX11::GetWidth() const
{
    return m_width;
}

int CTextureDirectX11::GetHeight() const
{
    return m_height;
}

ID3D11ShaderResourceView* CTextureDirectX11::GetShaderResourceView() const
{
    return m_shaderResourceView;
}

int CTextureDirectX11::GetPitch() const
{
    return m_pitch;
}

int CTextureDirectX11::GetBPP() const
{
    return m_bitsPerPixel;
}

void CTextureDirectX11::SetPixel(int a_x, int a_y, int a_color)
{
}
