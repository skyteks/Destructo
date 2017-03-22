#include "CRendererDirectX11.h"

CRendererDirectX11::CRendererDirectX11()
	: m_swapChain(nullptr)
	, m_renderTargetView(nullptr)
	, m_device(nullptr)
	, m_deviceContext(nullptr)
	, m_inputLayout(nullptr)
	, m_vertexBuffer(nullptr)
	, m_pixelShader(nullptr)
	, m_vertexShader(nullptr)
	, m_samplerState(nullptr)
	, m_blendState(nullptr)
	, m_shaderResourceView(nullptr)
{
	//memset(vertices, 0, sizeof(SVertex) * verticesMacCount);
}


CRendererDirectX11::~CRendererDirectX11()
{
	Shutdown();
}


bool CRendererDirectX11::Initialize(HWND a_hwnd)
{
	m_windowHandle = a_hwnd;

	m_windowDC = GetDC(m_windowHandle);

	bool wResult = false;

	RECT rc;
	wResult = GetClientRect(m_windowHandle, &rc) != 0;
	if (!wResult)
		return false;
	m_windowWidth = rc.right;
	m_windowHeight = rc.bottom;


	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Height = m_windowHeight;
	swapChainDesc.BufferDesc.Width = m_windowWidth;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 1;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 30;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.Flags = 0;
	swapChainDesc.OutputWindow = m_windowHandle;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = true;

	m_swapChain = nullptr;

	m_device = nullptr;

	m_deviceContext = nullptr;

	HRESULT hResult = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr, 0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_swapChain,
		&m_device,
		nullptr,
		&m_deviceContext
	);

	if (Failed(hResult))
		return false;

	ID3D11Texture2D* texture2D;

	hResult = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&texture2D));

	if (Failed(hResult))
		return false;

	hResult = m_device->CreateRenderTargetView(texture2D, nullptr, &m_renderTargetView);

	if (Failed(hResult))
		return false;

	texture2D->Release();
	//SafeRelease(texture2D);

	LoadShader();
	CreatePrimitives();

	// alpha blending
	D3D11_BLEND_DESC blendnDesc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());

	blendnDesc.RenderTarget[0].BlendEnable = true;
	blendnDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendnDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	hResult = m_device->CreateBlendState(&blendnDesc, &m_blendState);

	if (Failed(hResult))
		return false;

	float blendFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_deviceContext->OMSetBlendState(m_blendState, blendFactor, 0xFFFFFFFF);

	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr);

	return true;
}


ITexture* CRendererDirectX11::LoadTextureFromFile(char* a_path)
{
	SBitmap bmp = LoadBitmapAndAddAlpha(a_path);

	DXGI_SAMPLE_DESC sampleDesc = {
		1,
		0
	};

	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = bmp.m_header.x2;
	textureDesc.Height = bmp.m_header.y2;
	textureDesc.MipLevels = textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;//D3D11_USAGE_DYNAMIC;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0; // previous: D3D11_CPU_ACCESS_WRITE
	textureDesc.MiscFlags = 0;
	//	bmp.header.Width,
	//	bmp.header.Height,
	//	0,
	//	1,
	//	DXGI_FORMAT_R8G8B8A8_UNORM,
	//	sampleDesc,
	//	D3D11_USAGE_DEFAULT,
	//	D3D11_BIND_SHADER_RESOURCE,
	//	0,
	//	0
	//};

	D3D11_SUBRESOURCE_DATA textureData = {};
	textureData.pSysMem = bmp.m_data;
	textureData.SysMemPitch = bmp.m_header.x2 * 4;

	ID3D11Texture2D* directX11Texture = nullptr;

	HRESULT hResult = m_device->CreateTexture2D(&textureDesc, &textureData, &directX11Texture);

	free(bmp.m_data);
	bmp.m_data = nullptr;

	if (Failed(hResult))
		return nullptr;

	ID3D11ShaderResourceView* m_shaderResourceView;
	hResult = m_device->CreateShaderResourceView(directX11Texture, nullptr, &m_shaderResourceView);

	if (Failed(hResult))
		return nullptr;

	return new CTextureDirectX11(directX11Texture, m_shaderResourceView);
}


void CRendererDirectX11::DrawTexture(int a_posX, int a_posY, int a_width, int a_height, ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight)
{
	CTextureDirectX11* directX11Texture = reinterpret_cast<CTextureDirectX11*>(a_texture);

	m_deviceContext->PSSetShaderResources(0, 1, &m_shaderResourceView);
	if (m_shaderResourceView != directX11Texture->GetShaderResourceView())
	{
		Flush();
	}
	m_shaderResourceView = directX11Texture->GetShaderResourceView();

	SRect source;
	source.x1 = Map(a_posX, 0, m_windowWidth, -1, 1);
	source.y1 = Map(a_posY, 0, m_windowHeight, -1, 1);
	source.x2 = Map(a_width, 0, m_windowWidth, 0, 2);
	source.y2 = Map(a_height, 0, m_windowHeight, 0, 2);

	SRect dest;
	dest.x1 = Map(a_imgX, 0, a_texture->GetWidth(), 0, 1);
	dest.y1 = Map(a_texture->GetHeight() - a_imgY, 0, a_texture->GetHeight(), 0, 1);
	dest.x2 = Map(a_imgWidth, 0, a_texture->GetWidth(), 0, 1);
	dest.y2 = -Map(a_imgHeight, 0, a_texture->GetHeight(), 0, 1);

	if (vertexIndex > 0)
		vertices[vertexIndex++] = SVertex(source.x1, source.y1, 0, dest.x1, dest.y1 + dest.y2, 1, 1, 1, 1);

	vertices[vertexIndex++] = SVertex(source.x1, source.y1, 0, dest.x1, dest.y1, 1, 1, 1, 1);
	vertices[vertexIndex++] = SVertex(source.x1 + source.x2, source.y1, 0, dest.x1 + dest.x2, dest.y1, 1, 1, 1, 1);
	vertices[vertexIndex++] = SVertex(source.x1, source.y1 + source.y2, 0, dest.x1, dest.y1 + dest.y2, 1, 1, 1, 1);
	vertices[vertexIndex++] = SVertex(source.x1 + source.x2, source.y1 + source.y2, 0, dest.x1 + dest.x2, dest.y1 + dest.y2, 1, 1, 1, 1);

	vertices[vertexIndex++] = SVertex(source.x1 + source.x2, source.y1 + source.y2, 0, dest.x1 + dest.x2, dest.y1 + dest.y2, 1, 1, 1, 1);
}

void CRendererDirectX11::DrawString(int a_posX, int a_posY, const char* a_string, int a_textColor, int a_backgroundColor, UINT a_format, ITexture* a_fontTexture)
{
	if (a_string == nullptr)
		return;

	SRect source;
	SRect dest;

	unsigned int counter = 0;
	unsigned int newLines = 0;

	while (*a_string)
	{
		unsigned char c = *a_string++;

		source.x1 = (c % 16) * 16;
		source.y1 = (c / 16) * 16;
		source.x2 = 16;
		source.y2 = 16;

		dest.x1 = a_posX + counter * 16;
		dest.y1 = a_posY + (newLines * 16);
		dest.x2 = 16;
		dest.y2 = 16;

		if (c == '\n')
		{
			newLines++;
			counter = 0;
		}
		else
		{
			DrawTexture(dest.x1, dest.y1, dest.x2, dest.y2, a_fontTexture, source.x1, source.y1, source.x2, source.y2);
			counter++;
		}
	}
}


void CRendererDirectX11::Begin()
{
	float color[4] = { 1, 0, 1, 1 };
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);
}


void CRendererDirectX11::End()
{
	Flush();

	m_swapChain->Present(0, 0);
}


void CRendererDirectX11::Shutdown()
{
	SafeRelease(m_swapChain);
	SafeRelease(m_renderTargetView);
	SafeRelease(m_device);
	SafeRelease(m_deviceContext);
	SafeRelease(m_inputLayout);
	SafeRelease(m_vertexBuffer);
	SafeRelease(m_pixelShader);
	SafeRelease(m_vertexShader);
	SafeRelease(m_samplerState);
	SafeRelease(m_blendState);
}

bool CRendererDirectX11::Failed(HRESULT a_aResult)
{
	if (FAILED(a_aResult))
	{
		LPTSTR buffer;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, (DWORD)a_aResult, LANG_USER_DEFAULT, (LPTSTR)&buffer, 0, nullptr);

		MessageBox(0, buffer, TEXT("Fatal error"), MB_OK | MB_ICONERROR);
		LocalFree(buffer);
		return true;
	}
	return false;
}

bool CRendererDirectX11::LoadShader()
{
	ID3D10Blob* dataBlob = nullptr;
	ID3D10Blob* errorBlob = nullptr;

	HRESULT hResult;

	//pixel shader
	D3DX11CompileFromFile(
		"Shader.hlsl",
		nullptr,
		nullptr,
		"PS_Main",
		"ps_4_0",
		0, 0,
		nullptr,
		&dataBlob,
		&errorBlob,
		&hResult);

	if (errorBlob)
		OutputDebugStringA((LPCSTR)errorBlob->GetBufferPointer());

	if (Failed(hResult))
		return false;

	m_pixelShader = nullptr;

	hResult = m_device->CreatePixelShader(
		dataBlob->GetBufferPointer(),
		dataBlob->GetBufferSize(),
		0,
		&m_pixelShader
	);

	if (dataBlob != nullptr)
		dataBlob->Release();
	if (errorBlob != nullptr)
		errorBlob->Release();

	if (Failed(hResult))
		return false;

	D3DX11CompileFromFile(
		"Shader.hlsl",
		nullptr,
		nullptr,
		"VS_Main",
		"vs_4_0",
		0, 0,
		nullptr,
		&dataBlob,
		&errorBlob,
		&hResult);

	if (errorBlob)
		OutputDebugStringA((LPCSTR)errorBlob->GetBufferPointer());

	if (Failed(hResult))
		return false;

	m_deviceContext->PSSetShader(m_pixelShader, nullptr, 0);

	//vertex shader
	m_vertexShader = nullptr;

	hResult = m_device->CreateVertexShader(
		dataBlob->GetBufferPointer(),
		dataBlob->GetBufferSize(),
		0,
		&m_vertexShader
	);

	if (Failed(hResult))
		return false;

	D3D11_INPUT_ELEMENT_DESC layoutDesc[] = {
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		{
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		{
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		}
	};

	hResult = m_device->CreateInputLayout(
		layoutDesc,
		3,
		dataBlob->GetBufferPointer(),
		dataBlob->GetBufferSize(),
		&m_inputLayout
	);

	if (Failed(hResult))
		return false;

	m_deviceContext->VSSetShader(m_vertexShader, nullptr, 0);

	if (dataBlob != nullptr)
	{
		//printf("%s\n", dataBlob->GetBufferPointer());
		dataBlob->Release();
	}
	if (errorBlob != nullptr)
	{
		//printf("%s\n", errorBlob->GetBufferPointer());
		errorBlob->Release();
	}

	return true;
}

bool CRendererDirectX11::CreatePrimitives()
{
	//vertex buffer
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(SVertex) * verticesMacCount;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.StructureByteStride = 0;

	HRESULT result = m_device->CreateBuffer(&bufferDesc, nullptr, &m_vertexBuffer);

	if (Failed(result))
	{
		return false;
	}

	UINT stride = sizeof(SVertex);
	UINT offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	//render target view
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr);

	// primitive topology
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//viewport
	D3D11_VIEWPORT viewport = { 0 };
	viewport.Height = m_windowHeight;
	viewport.Width = m_windowWidth;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	m_deviceContext->RSSetViewports(1, &viewport);

	//input layout
	m_deviceContext->IASetInputLayout(m_inputLayout);

	return true;
}

void CRendererDirectX11::Draw()
{
	//deviceContext->Draw(4, 0);
}

void CRendererDirectX11::Flush()
{
	D3D11_MAPPED_SUBRESOURCE subresource = { 0 };

	HRESULT result = m_deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subresource);

	if (Failed(result))
		return;

	memcpy(subresource.pData, vertices, sizeof(vertices));

	m_deviceContext->Unmap(m_vertexBuffer, 0);

	m_deviceContext->Draw(vertexIndex, 0);
	vertexIndex = 0;
}