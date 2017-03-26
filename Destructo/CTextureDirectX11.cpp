#include "CTextureDirectX11.h"



CTextureDirectX11::CTextureDirectX11(ID3D11Texture2D* a_texture, ID3D11ShaderResourceView* a_shaderResView)
{
	m_texture = a_texture;
	D3D11_TEXTURE2D_DESC textureDesc;
	m_texture->GetDesc(&textureDesc);
	x2 = textureDesc.Width;
	y2 = textureDesc.Height;

	m_shaderResourceView = a_shaderResView;
}


CTextureDirectX11::~CTextureDirectX11()
{
	SafeRelease(m_texture);
	SafeRelease(m_shaderResourceView);
}

int CTextureDirectX11::GetWidth()
{
	return x2;
}

int CTextureDirectX11::GetHeight()
{
	return y2;
}

ID3D11ShaderResourceView* CTextureDirectX11::GetShaderResourceView()
{
	return m_shaderResourceView;
}

int CTextureDirectX11::GetPitch()
{
	return m_pitch;
}

int CTextureDirectX11::GetBPP()
{
	return m_bitsPerPixel;
}
