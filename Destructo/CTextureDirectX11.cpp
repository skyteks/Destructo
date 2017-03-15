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

}

int CTextureDirectX11::GetWidth()
{
	return m_width;
}

int CTextureDirectX11::GetHeight()
{
	return m_height;
}

ID3D11ShaderResourceView* CTextureDirectX11::GetShaderResourceView()
{
	return m_shaderResourceView;
}
