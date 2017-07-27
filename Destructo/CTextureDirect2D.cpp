#include "CTextureDirect2D.h"

ID2D1HwndRenderTarget* CTextureDirect2D::s_renderTarget = nullptr;

CTextureDirect2D::CTextureDirect2D(std::string a_path)
    : m_bitmap(nullptr)
{
    // image loading with factory
    IWICImagingFactory *imageFactory = nullptr;
    IWICBitmapDecoder *decoder = nullptr;
    IWICBitmapFrameDecode *frameDecoder = nullptr;
    IWICFormatConverter *converter = nullptr;

    // create factory
    HRESULT hResult = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, reinterpret_cast<LPVOID*>(&imageFactory));
    if (!SUCCEEDED(hResult))
        return;

    // https://msdn.microsoft.com/en-us/library/windows/desktop/mt745029(v=vs.85).aspx
    // https://msdn.microsoft.com/en-us/library/windows/desktop/dd370990(v=vs.85).aspx

    wchar_t wtext[MAX_PATH] = {};
    mbstowcs(wtext, a_path.c_str(), strlen(a_path.c_str()) + 1);//Plus null

    // create decoder
    hResult = imageFactory->CreateDecoderFromFilename(wtext, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
    if (!SUCCEEDED(hResult))
        goto broke;

    // get frame
    hResult = decoder->GetFrame(0, &frameDecoder);
    if (!SUCCEEDED(hResult))
        goto broke;

    // create converter
    hResult = imageFactory->CreateFormatConverter(&converter);
    if (!SUCCEEDED(hResult))
        goto broke;

    // initialize converter
    hResult = converter->Initialize(frameDecoder, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeMedianCut);
    if (!SUCCEEDED(hResult))
        goto broke;

    // create bitmap
    hResult = s_renderTarget->CreateBitmapFromWicBitmap(converter, nullptr, &m_bitmap);
    if (!SUCCEEDED(hResult))
        goto broke;

    // get width & height
    D2D1_SIZE_F size = m_bitmap->GetSize();
    m_width = (int)size.width;
    m_height = (int)size.height;
    if (!SUCCEEDED(hResult))
        goto broke;

broke:
    // free resources
    SafeRelease(imageFactory);
    SafeRelease(decoder);
    SafeRelease(frameDecoder);
    SafeRelease(converter);
}


CTextureDirect2D::~CTextureDirect2D()
{
    SafeRelease(m_bitmap);
}


int CTextureDirect2D::GetWidth() const
{
    return m_width;
}


int CTextureDirect2D::GetHeight() const
{
    return m_height;
}

ID2D1Bitmap* CTextureDirect2D::GetBitmapHandle() const
{
    return m_bitmap;
}

void CTextureDirect2D::SetPixel(int a_x, int a_y, int a_color)
{
}

int CTextureDirect2D::GetPitch() const
{
    return m_pitch;
}

int CTextureDirect2D::GetBPP() const
{
    return m_bitsPerPixel;
}


