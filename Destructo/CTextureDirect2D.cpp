#include "CTextureDirect2D.h"

ID2D1HwndRenderTarget* CTextureDirect2D::s_renderTarget = nullptr;

CTextureDirect2D::CTextureDirect2D(char* a_path)
	: m_bitmap(nullptr)
{
	// image loading with factory
	IWICImagingFactory *imageFactory = nullptr;
	IWICBitmapDecoder *decoder = nullptr;
	IWICBitmapFrameDecode *frameDecoder = nullptr;
	IWICFormatConverter *converter = nullptr;
	
	//ID2D1Bitmap

	/*
	What I think you want is a regular WIC bitmap, IWICBitmap, 
	which you can create with IWICImagingFactory::CreateBitmap().
	From there you can call Lock() to get at the buffer, and then read/write
	using pointers and do whatever you want. Then, when you need to draw it
	on-screen with Direct2D, use ID2D1RenderTarget::CreateBitmap() to create
	a new device bitmap, or ID2D1Bitmap::CopyFromMemory() to update an existing
	device bitmap. You can also render into an IWICBitmap by making use of
	ID2D1Factory::CreateWicBitmapRenderTarget() (not hardware accelerated).
	
	*/
	//s_renderTarget->CreateBitmap()
	

	// create factory
	HRESULT hResult = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, reinterpret_cast<LPVOID*>(&imageFactory));
	if (!SUCCEEDED(hResult))
		return;

	// https://msdn.microsoft.com/en-us/library/windows/desktop/mt745029(v=vs.85).aspx
	// https://msdn.microsoft.com/en-us/library/windows/desktop/dd370990(v=vs.85).aspx

	wchar_t wtext[MAX_PATH] = {};
	mbstowcs(wtext, a_path, strlen(a_path) + 1);//Plus null

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


int CTextureDirect2D::GetWidth()
{
	return m_width;
}


int CTextureDirect2D::GetHeight()
{
	return m_height;
}

ID2D1Bitmap * CTextureDirect2D::GetBitmapHandle()
{
	return m_bitmap;
}

void CTextureDirect2D::SetPixel(int a_x, int a_y, int a_color)
{
}

int CTextureDirect2D::GetPitch()
{
	return m_pitch;
}

int CTextureDirect2D::GetBPP()
{
	return m_bitsPerPixel;
}


