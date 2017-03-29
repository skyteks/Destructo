#pragma once

#include <d3d11.h>
#include <d3dx11async.h>
#include <DirectXMath.h>
#include <D3DX11.h>

#include "ITexture.h"
#include "GlobalFunctions.h"

#pragma comment(lib, "d3d11.lib")

class CTextureDirectX11 : public ITexture
{
public:
	CTextureDirectX11(ID3D11Texture2D* a_texture, ID3D11ShaderResourceView* a_shaderResView);

	~CTextureDirectX11();

	int GetWidth();

	int GetHeight();

	int GetPitch();

	int GetBPP();

	void SetPixel(int a_x, int a_y, int a_color);

	ID3D11ShaderResourceView* GetShaderResourceView();

private:

	int m_width;
	int m_height;
	int m_pitch;
	int m_bitsPerPixel;
	bool m_isLocked;

	UINT* m_data = nullptr;
	ID3D11Texture2D* m_texture = nullptr;
	ID3D11ShaderResourceView* m_shaderResourceView = nullptr;
};

