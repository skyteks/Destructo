#include "CRendererDirectX11.h"
#include "CGameObject.h"
#include "CTransform.h"
#include "CSprite.h"

CRendererDirectX11::CRendererDirectX11()
    : m_windowWidth(0)
    , m_windowHeight(0)
    , vertices()
    , m_swapChain(nullptr)
    , m_renderTargetView(nullptr)
    , m_device(nullptr)
    , m_deviceContext(nullptr)
    , m_inputLayout(nullptr)
    , m_vertexBuffer(nullptr)
    , m_pixelShader(nullptr)
    , m_vertexShader(nullptr)
    , m_samplerState(nullptr)
    , m_blendState(nullptr)
    //, m_shaderResourceView(nullptr)
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


ITexture* CRendererDirectX11::LoadTextureFromFile(std::string a_path)
{
    SBitmap bmp = LoadBitmapAndAddAlpha(a_path);

    DXGI_SAMPLE_DESC sampleDesc = {
        1,
        0
    };

    D3D11_TEXTURE2D_DESC textureDesc = {};
    textureDesc.Width = bmp.m_header.m_width;
    textureDesc.Height = bmp.m_header.m_height;
    textureDesc.MipLevels = textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;//D3D11_USAGE_DYNAMIC;
    textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    textureDesc.CPUAccessFlags = 0; // previous: D3D11_CPU_ACCESS_WRITE
    textureDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA textureData = {};
    textureData.pSysMem = bmp.m_data;
    textureData.SysMemPitch = bmp.m_header.m_width * 4;

    ID3D11Texture2D* texture2D = nullptr;

    HRESULT hResult = m_device->CreateTexture2D(&textureDesc, &textureData, &texture2D);

    bmp.FreeData();

    if (Failed(hResult))
        return nullptr;

    ID3D11ShaderResourceView* m_shaderResourceView;
    hResult = m_device->CreateShaderResourceView(texture2D, nullptr, &m_shaderResourceView);

    if (Failed(hResult))
        return nullptr;

    return new CTextureDirectX11(texture2D, m_shaderResourceView);
}


void CRendererDirectX11::DrawObject(CGameObject& a_gameObject)
{
    const CTextureDirectX11* directX11Texture = static_cast<const CTextureDirectX11*>(CTextureManager::GetInstance().GetTextureByName(a_gameObject.GetComponent<CSprite>()->GetTextureName()));
    const CTextureDirectX11* directX11OpacityMask = nullptr;
    if (a_gameObject.GetComponent<CSprite>()->GetOpacityMaskName() != "")
    {
        directX11OpacityMask = static_cast<const CTextureDirectX11*>(CTextureManager::GetInstance().GetTextureByName(a_gameObject.GetComponent<CSprite>()->GetOpacityMaskName()));
    }

    SVector3 position = a_gameObject.GetComponent<CTransform>()->GetPosition();
    SVector3 scale = a_gameObject.GetComponent<CTransform>()->GetScale();

    SRect<float> dest;
    dest.x1 = LinearRemap(a_gameObject.GetComponent<CSprite>()->GetImageSection().x1, 0.0f, static_cast<float>(directX11Texture->GetWidth()), 0.0f, 1.0f);
    dest.y1 = LinearRemap(directX11Texture->GetHeight() - a_gameObject.GetComponent<CSprite>()->GetImageSection().y1, 0.0f, static_cast<float>(directX11Texture->GetHeight()), 0.0f, 1.0f);
    dest.x2 = LinearRemap(a_gameObject.GetComponent<CSprite>()->GetImageSection().x2, 0.0f, static_cast<float>(directX11Texture->GetWidth()), 0.0f, 1.0f);
    dest.y2 = -1.0f * LinearRemap(a_gameObject.GetComponent<CSprite>()->GetImageSection().y2, 0.0f, static_cast<float>(directX11Texture->GetHeight()), 0.0f, 1.0f);

    SRect<float> source;
    source.x1 = LinearRemap(position.x, 0.0f, static_cast<float>(m_windowWidth), -1.0f, 1.0f);
    source.y1 = LinearRemap(position.y, 0.0f, static_cast<float>(m_windowHeight), -1.0f, 1.0f);
    source.x2 = LinearRemap(static_cast<float>(directX11Texture->GetWidth()) * scale.x, 0.0f, static_cast<float>(m_windowWidth), 0.0f, 2.0f);
    source.y2 = LinearRemap(static_cast<float>(directX11Texture->GetHeight()) * scale.y, 0.0f, static_cast<float>(m_windowHeight), 0.0f, 2.0f);

    // rotate
    if (dest.x1 != 0.0f && dest.y1 != 0.0f)
    {
        dest.x1 -= position.x + dest.x2 / 2.0f;
        dest.y1 -= position.y + dest.y2 / 2.0f;
    }

    SVector3 vec1(dest.x1, dest.y1);
    SVector3 vec2(dest.x1 + dest.x2, dest.y1);
    SVector3 vec3(dest.x1, dest.y1 + dest.y2);
    SVector3 vec4(dest.x1 + dest.x2, dest.y1 + dest.y2);
    SMatrix4x4 rotation = SMatrix4x4::RotationZ(a_gameObject.GetComponent<CTransform>()->GetRotation().z);

    SVector4 point1 = rotation * vec1;
    SVector4 point2 = rotation * vec2;
    SVector4 point3 = rotation * vec3;
    SVector4 point4 = rotation * vec4;

    if (dest.x1 != 0.0f && dest.y1 != 0.0f)
    {
        dest.x1 += position.x + dest.x2 / 2.0f;
        dest.y1 += position.y + dest.y2 / 2.0f;
    }

    //point1.x += dest.x1;
    //point2.x += dest.x1;
    //point3.x += dest.x1;
    //point4.x += dest.x1;
    //
    //point1.y += dest.y1;
    //point2.y += dest.y1;
    //point3.y += dest.y1;
    //point4.y += dest.y1;

    //if (vertexIndex > 0)
    //	vertices[vertexIndex++] = SVertex(source.x1, source.y1 + source.y2, 0.0f, point3.x, point3.y, 1.0f, 1.0f, 1.0f, 1.0f);

    vertices[vertexIndex++] = SVertex(source.x1, source.y1, 0.0f, point1.x, point1.y, 1.0f, 1.0f, 1.0f, 1.0f);
    vertices[vertexIndex++] = SVertex(source.x1 + source.x2, source.y1, 0.0f, point2.x, point2.y, 1.0f, 1.0f, 1.0f, 1.0f);
    vertices[vertexIndex++] = SVertex(source.x1, source.y1 + source.y2, 0.0f, point3.x, point3.y, 1.0f, 1.0f, 1.0f, 1.0f);
    vertices[vertexIndex++] = SVertex(source.x1 + source.x2, source.y1 + source.y2, 0.0f, point4.x, point4.y, 1.0f, 1.0f, 1.0f, 1.0f);

    //vertices[vertexIndex++] = SVertex(source.x1 + source.x2, source.y1 + source.y2, 0.0f, point4.x, point4.y, 1.0f, 1.0f, 1.0f, 1.0f);

    ID3D11ShaderResourceView* shaderResourceView = directX11Texture->GetShaderResourceView();
    m_deviceContext->PSSetShaderResources(0, 1, &shaderResourceView);
    if (directX11OpacityMask != nullptr)
    {
        ID3D11ShaderResourceView* shaderResourceView = directX11OpacityMask->GetShaderResourceView();
        m_deviceContext->PSSetShaderResources(1, 1, &shaderResourceView);
    }
    Flush();
}


void CRendererDirectX11::DrawTexture(int a_posX, int a_posY, int a_width, int a_height, const ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight)
{
    const CTextureDirectX11* directX11Texture = reinterpret_cast<const CTextureDirectX11*>(a_texture);

    SRect<float> source;
    source.x1 = LinearRemap(static_cast<float>(a_posX), 0.0f, static_cast<float>(m_windowWidth), -1.0f, 1.0f);
    source.y1 = LinearRemap(static_cast<float>(a_posY), 0.0f, static_cast<float>(m_windowHeight), -1.0f, 1.0f);
    source.x2 = LinearRemap(static_cast<float>(a_width), 0.0f, static_cast<float>(m_windowWidth), 0.0f, 2.0f);
    source.y2 = LinearRemap(static_cast<float>(a_height), 0.0f, static_cast<float>(m_windowHeight), 0.0f, 2.0f);

    SRect<float> dest;
    dest.x1 = LinearRemap(static_cast<float>(a_imgX), 0.0f, static_cast<float>(a_texture->GetWidth()), 0.0f, 1.0f);
    dest.y1 = LinearRemap(static_cast<float>(a_texture->GetHeight() - a_imgY), 0.0f, static_cast<float>(a_texture->GetHeight()), 0.0f, 1.0f);
    dest.x2 = LinearRemap(static_cast<float>(a_imgWidth), 0.0f, static_cast<float>(a_texture->GetWidth()), 0.0f, 1.0f);
    dest.y2 = -LinearRemap(static_cast<float>(a_imgHeight), 0.0f, static_cast<float>(a_texture->GetHeight()), 0.0f, 1.0f);

    //if (vertexIndex > 0)
    //    vertices[vertexIndex++] = SVertex(source.x1, source.y1, 0.0f, dest.x1, dest.y1 + dest.y2, 1.0f, 1.0f, 1.0f, 1.0f);

    vertices[vertexIndex++] = SVertex(source.x1, source.y1, 0.0f, dest.x1, dest.y1, 1.0f, 1.0f, 1.0f, 1.0f);
    vertices[vertexIndex++] = SVertex(source.x1 + source.x2, source.y1, 0.0f, dest.x1 + dest.x2, dest.y1, 1.0f, 1.0f, 1.0f, 1.0f);
    vertices[vertexIndex++] = SVertex(source.x1, source.y1 + source.y2, 0.0f, dest.x1, dest.y1 + dest.y2, 1.0f, 1.0f, 1.0f, 1.0f);
    vertices[vertexIndex++] = SVertex(source.x1 + source.x2, source.y1 + source.y2, 0.0f, dest.x1 + dest.x2, dest.y1 + dest.y2, 1.0f, 1.0f, 1.0f, 1.0f);

    //vertices[vertexIndex++] = SVertex(source.x1 + source.x2, source.y1 + source.y2, 0.0f, dest.x1 + dest.x2, dest.y1 + dest.y2, 1.0f, 1.0f, 1.0f, 1.0f);

    ID3D11ShaderResourceView* shaderResourceView = directX11Texture->GetShaderResourceView();
    m_deviceContext->PSSetShaderResources(0, 1, &shaderResourceView);
    //m_deviceContext->PSSetShaderResources(0, 1, &m_shaderResourceView);
    //if (m_shaderResourceView != directX11Texture->GetShaderResourceView())
    //{
    Flush();
    //}
    //m_shaderResourceView = directX11Texture->GetShaderResourceView();
}


void CRendererDirectX11::DrawTextureWithOpacityMask(int a_posX, int a_posY, int a_width, int a_height, const ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight, const ITexture* a_opacityMask)
{
}


void CRendererDirectX11::DrawString(int a_posX, int a_posY, const char* a_string, int a_textColor, int a_backgroundColor, UINT a_format, const ITexture* a_fontTexture)
{
    if (a_string == nullptr)
        return;

    SRect<int> source;
    SRect<int> dest;

    uint32_t counter = 0;
    uint32_t newLines = 0;

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
    float color[4] = { 1.0f, 0.0f, 1.0f, 1.0f };
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
        },
        //{
        //	"BOOL",
        //	0,
        //	DXGI_FORMAT_R32_UINT,
        //	0,
        //	D3D11_APPEND_ALIGNED_ELEMENT,
        //	D3D11_INPUT_PER_VERTEX_DATA,
        //	0
        //},
        //{
        //	"COLOR",
        //	0,
        //	DXGI_FORMAT_R32G32B32A32_FLOAT,
        //	0,
        //	D3D11_APPEND_ALIGNED_ELEMENT,
        //	D3D11_INPUT_PER_VERTEX_DATA,
        //	0
        //}
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
    viewport.Height = static_cast<float>(m_windowHeight);
    viewport.Width = static_cast<float>(m_windowWidth);
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
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