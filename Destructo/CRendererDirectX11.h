#pragma once

#include <d3d11.h>
#include <d3dx11async.h>
#include <DirectXMath.h>
#include <D3DX11.h>

//#include <vector>

#include "IRenderer.h"
#include "CTextureDirectX11.h"
#include "GlobalFunctions.h"
#include "SRect.h"
#include "SVertex.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

class CRendererDirectX11 : public IRenderer
{
public:
	CRendererDirectX11();

	~CRendererDirectX11();

	bool InitializeGraphics(HWND a_hwnd);

	ITexture* LoadTextureFromFile(char* a_path);

	void Begin();

	void DrawTexture(int a_posX, int a_posY, int a_width, int a_height, ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight);

	void DrawString(int a_posX, int a_posY, const char* a_string, int a_textColor, int a_backgroundColor, UINT a_format, ITexture* a_fontTexture);

	void End();

	void ShutdownGraphics();

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

	HRESULT hResult;
	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11RenderTargetView* m_renderTargetView = nullptr;
	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_deviceContext = nullptr;
	ID3D11InputLayout* m_inputLayout = nullptr;
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11VertexShader* m_vertexShader = nullptr;
	D3D11_PRIMITIVE_TOPOLOGY primitiveTopology;
	ID3D11SamplerState* m_samplerState = nullptr;
	ID3D11BlendState* m_blendState = nullptr;
	ID3D11ShaderResourceView* m_shaderResourceView = nullptr;
};

