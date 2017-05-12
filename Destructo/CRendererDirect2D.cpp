#include "CRendererDirect2D.h"

CRendererDirect2D::CRendererDirect2D()
	: m_imageFactory(nullptr)
	, m_renderTarget(nullptr)
	, m_writeFactory(nullptr)
	, m_writeTextFormat(nullptr)
	, m_colorBrush(nullptr)
	, m_clearColor(0)
{

}


CRendererDirect2D::~CRendererDirect2D()
{

}


bool CRendererDirect2D::Initialize(HWND a_hwnd)
{
	m_windowHandle = a_hwnd;
	m_windowDC = GetDC(a_hwnd);

	bool wResult = false;

	// create imageFactory
	HRESULT hResult = D2D1CreateFactory<ID2D1Factory>(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_imageFactory);
	if (m_imageFactory == nullptr)
	{
		return false;
	}

	// create render target
	//ComPtr<ID2D1Effect> blendEffect;
	//m_d2dContext->CreateEffect(CLSID_D2D1Blend, &blendEffect);

	//blendEffect->SetInput(0, bitmap);
	//blendEffect->SetInput(1, bitmapTwo);
	//blendEffect->SetValue(D2D1_BLEND_PROP_MODE, D2D1_BLEND_MODE_EXCLUSION);

	//m_d2dContext->BeginDraw();
	//m_d2dContext->DrawImage(blendEffect.Get());
	//m_d2dContext->EndDraw();


	// get window borders
	RECT rc;
	wResult = GetClientRect(m_windowHandle, &rc);
	if (!wResult)
		return false;
	m_windowWidth = rc.right;
	m_windowHeight = rc.bottom;

	D2D1_SIZE_U size = D2D1::SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top);

	hResult = m_imageFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(m_windowHandle, size, D2D1_PRESENT_OPTIONS_IMMEDIATELY),
		&m_renderTarget);

	if (m_renderTarget == nullptr)
		return false;
	else
	{
		// set global renderTarget to current renderTarget, to create bitmaps from it
		CTextureDirect2D::s_renderTarget = m_renderTarget;
	}
	
	// create brush
	hResult = m_renderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Yellow),
		&m_colorBrush);
	if (m_colorBrush == nullptr)
		return false;

	// set clear color
	D2D1::ColorF clr(RGB(255, 0, 255), 255.0f);
	m_clearColor = clr;

	// create writefactory to create text
	hResult = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_writeFactory),
		reinterpret_cast<IUnknown **>(&m_writeFactory));
	if (m_writeFactory == nullptr)
		return false;

	// create textformat object
	hResult = m_writeFactory->CreateTextFormat(
		L"OCR A Std", // font
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		14, // size
		L"",
		&m_writeTextFormat
	);

	return true;
}


ITexture * CRendererDirect2D::LoadTextureFromFile(const char * a_path)
{
	return new CTextureDirect2D(a_path);
}


void CRendererDirect2D::Begin()
{
	m_renderTarget->BeginDraw();
}

void CRendererDirect2D::DrawObject(CGameObject& a_gameObject)
{
	CTextureDirect2D* direct2DTexture = reinterpret_cast<CTextureDirect2D*>(CTextureManager::GetInstance().GetTextureByName(a_gameObject.GetTextureName()));
	CTextureDirect2D* direct2DOpacityMask = nullptr;
	if (a_gameObject.GetOpacityMaskName() != nullptr)
	{
		direct2DOpacityMask = reinterpret_cast<CTextureDirect2D*>(CTextureManager::GetInstance().GetTextureByName(a_gameObject.GetOpacityMaskName()));
	}

	SVector3 position = a_gameObject.GetPosition();
	SVector3 scale = a_gameObject.GetScale();
	SMatrix4x4 rotation = a_gameObject.GetRotation();

	D2D1_RECT_F rect;
	rect.left = position.x;
	rect.top = position.y;
	rect.right = position.x + direct2DTexture->GetWidth() * scale.x;
	rect.bottom = position.y + direct2DTexture->GetHeight() * scale.y;

	D2D1_MATRIX_3X2_F rot;
	rot._11 = rotation.m11;
	rot._12 = rotation.m12;
	rot._21 = rotation.m21;
	rot._22 = rotation.m22;
	rot._31 = rotation.m31;
	rot._32 = rotation.m32;
	m_renderTarget->SetTransform(rot);

	m_renderTarget->DrawBitmap(direct2DTexture->GetBitmapHandle(), rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, nullptr);
}


void CRendererDirect2D::DrawTexture(int a_posX, int a_posY, int a_width, int a_height, ITexture * a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight)
{
	CTextureDirect2D* direct2DTexture = reinterpret_cast<CTextureDirect2D*>(a_texture);

	D2D1_RECT_F rect;
	rect.left = a_posX;
	rect.top = a_posY;
	rect.right = a_posX + a_width;
	rect.bottom = a_posY + a_height;

	m_renderTarget->DrawBitmap(direct2DTexture->GetBitmapHandle(), rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, nullptr);
}

void CRendererDirect2D::DrawTextureWithOpacityMask(int a_posX, int a_posY, int a_width, int a_height, ITexture * a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight, ITexture * a_opacityMask)
{

}


void CRendererDirect2D::DrawString(int a_posX, int a_posY, const char* a_string, int a_textColor, int a_backgroundColor, UINT a_format, ITexture * a_fontTexture)
{
	if (a_string == nullptr)
		return;

	if (a_fontTexture == nullptr)
	{
		RECT rect;
		GetClientRect(m_windowHandle, &rect);

		unsigned int textLength = strlen(a_string);

		D2D1_RECT_F layoutRect = D2D1::RectF(
			(float)a_posX,
			(float)a_posY,
			(float)(a_posX + textLength * m_writeTextFormat->GetFontSize()), // X +  chars count * charactersize
			(float)(a_posY + textLength * m_writeTextFormat->GetFontSize()));

		// convert color to D2D1_COLOR_F
		D2D1::ColorF colorConverter = D2D1::ColorF(a_textColor, 1.0f);

		// set new brush color        
		m_colorBrush->SetColor(NewColor(a_textColor));

		
		wchar_t wtext[MAX_PATH] = {};
		mbstowcs(wtext, a_string, textLength + 1);//Plus null

		m_renderTarget->DrawText(
			wtext,
			textLength,
			m_writeTextFormat,
			layoutRect,
			m_colorBrush);
	}
	else
	{
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
}


void CRendererDirect2D::End()
{
	m_renderTarget->EndDraw();
}


void CRendererDirect2D::Shutdown()
{
	SafeRelease(m_imageFactory);
	SafeRelease(m_renderTarget);
	SafeRelease(m_colorBrush);
	SafeRelease(m_writeFactory);
	SafeRelease(m_writeTextFormat);
}

D2D1_COLOR_F CRendererDirect2D::NewColor(int a_color)
{
	// convert color to D2D1_COLOR_F
	D2D1::ColorF colorConverter = D2D1::ColorF(a_color, 1.0f);

	// rotating BGR to RGB
	if (true)// for easy toggle
	{
		float newR = colorConverter.b;
		colorConverter.b = colorConverter.r;
		colorConverter.r = newR;
	}

	D2D1_COLOR_F newColor;
	newColor.a = colorConverter.a;
	newColor.r = colorConverter.r;
	newColor.g = colorConverter.g;
	newColor.b = colorConverter.b;
	return newColor;
}

void CRendererDirect2D::Clear(int a_color)
{
	m_renderTarget->Clear(NewColor(a_color));
}
