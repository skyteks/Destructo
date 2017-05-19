#pragma once

#include <d3d11.h>
#include <d3dx11async.h>
#include <DirectXMath.h>
#include <D3DX11.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

//#include <vector>

#include "IRenderer.h"
#include "CTextureDirectX11.h"
#include "GlobalFunctions.h"
#include "SRect.h"
#include "SVertex.h"
#include "CTextureManager.h"

class CRendererDirectX11 : public IRenderer
{
public:
	CRendererDirectX11();

	~CRendererDirectX11() override;

	bool Initialize(HWND a_hwnd) override;

	ITexture* LoadTextureFromFile(std::string a_path) override;

	void Begin() override;

	void DrawObject(CGameObject& a_gameObject) override;

	void DrawTexture(int a_posX, int a_posY, int a_width, int a_height, ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight) override;

	void DrawTextureWithOpacityMask(int a_posX, int a_posY, int a_width, int a_height, ITexture * a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight, ITexture * a_opacityMask) override;

	void DrawString(int a_posX, int a_posY, const char* a_string, int a_textColor, int a_backgroundColor, UINT a_format, ITexture* a_fontTexture) override;

	void End() override;

	void Shutdown() override;

	bool Failed(HRESULT a_aResult);

	bool LoadShader();

	bool CreatePrimitives();

	void Draw();

	void Flush();

private:
	HWND m_windowHandle;
	HDC m_windowDC;
	int m_windowWidth;
	int m_windowHeight;

	static const int verticesMacCount = 1024;
	SVertex vertices[verticesMacCount];
	//std::vector<SVertex> vertices;
	int vertexIndex = 0;

	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11RenderTargetView* m_renderTargetView = nullptr;
	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_deviceContext = nullptr;
	ID3D11InputLayout* m_inputLayout = nullptr;
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11VertexShader* m_vertexShader = nullptr;
	D3D11_PRIMITIVE_TOPOLOGY m_primitiveTopology;
	ID3D11SamplerState* m_samplerState = nullptr;
	ID3D11BlendState* m_blendState = nullptr;
	ID3D11ShaderResourceView* m_shaderResourceView = nullptr;
};

