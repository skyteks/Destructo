#include "CRendererGDI.h"

CRendererGDI::CRendererGDI()
{

}


CRendererGDI::~CRendererGDI()
{

}


bool CRendererGDI::Initialize(HWND a_hwnd)
{
	m_windowHandle = a_hwnd;

	m_windowDC = GetDC(m_windowHandle);

	bool wResult = false;

	RECT rc;
	wResult = GetClientRect(m_windowHandle, &rc);
	if (!wResult)
		return false;
	m_windowWidth = rc.right;
	m_windowHeight = rc.bottom;



	m_backBufferBitmap = CreateCompatibleBitmap(m_windowDC, m_windowWidth, m_windowHeight);
	m_backbufferDC = CreateCompatibleDC(m_windowDC);
	HBITMAP tmpBmp = (HBITMAP)SelectObject(m_backbufferDC, m_backBufferBitmap);

	wResult = DeleteObject(tmpBmp);
	if (!wResult)
		return false;

	return true;
}

ITexture* CRendererGDI::LoadTextureFromFile(const char* a_path)
{
	return new CTextureGDI(a_path);
}


void CRendererGDI::DrawTexture(int a_posX, int a_posY, int a_width, int a_height, ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight)
{
	CTextureGDI* openGLTexture = reinterpret_cast<CTextureGDI*>(a_texture);

	TransparentBlt(m_backbufferDC, a_posX, a_posY, a_width, a_height, openGLTexture->GetBitmapDeviceContect(), a_imgX, a_imgY, a_imgWidth, a_imgHeight, RGB(255, 0, 255));
}

void CRendererGDI::DrawTextureWithOpacityMask(int a_posX, int a_posY, int a_width, int a_height, ITexture * a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight, ITexture * a_opacityMask)
{

}

//void CRendererGDI::MakeCircleInTexture(int a_posX, int a_posY, CTextureGDI* a_texture, int a_color, int a_radius)
//{
//	if (a_texture->GetWidth() < a_posX - a_radius || a_texture->GetHeight() < a_posY - a_radius || a_posX + a_radius < 0 || a_posY + a_radius < 0 || a_radius == 0)
//		return;
//
//	Ellipse(a_texture->GetBitmapDeviceContect(), a_posX, a_posY, a_posX - a_radius, a_posY - a_radius);
//	//for (int y = a_posY; y < a_posY - a_radius; y++)
//	//{
//	//	for (int x = a_posX; x < a_posX - a_radius; x++)
//	//	{
//	//		//SetPixel(a_texture->GetBitmapDeviceContect(), x, y, 255 * 255 * 255);
//	//	}
//	//}
//}


void CRendererGDI::DrawString(int a_posX, int a_posY, const char* a_string, int a_textColor, int a_backgroundColor, UINT a_format, ITexture* a_fontTexture)
{
	if (a_string == nullptr)
		return;

	if (a_fontTexture == nullptr)
	{
		RECT rc;
		rc.top = a_posY;
		rc.left = a_posX;
		rc.right = m_windowWidth;
		rc.bottom = m_windowHeight;

		int oldTextColor = GetTextColor(m_backbufferDC);
		int oldBkMode = GetBkMode(m_backbufferDC);

		SetBkMode(m_backbufferDC, TRANSPARENT);
		SetTextColor(m_backbufferDC, a_textColor);

		//DrawText(backbufferDC, string, -1, &rc, DT_TOP | DT_LEFT);
		DrawText(m_backbufferDC, a_string, -1, &rc, DT_CALCRECT);
		DrawText(m_backbufferDC, a_string, -1, &rc, a_format);

		SetBkColor(m_backbufferDC, oldBkMode);
		SetTextColor(m_backbufferDC, oldTextColor);
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


void CRendererGDI::Begin()
{
	BitBlt(m_windowDC, 0, 0, m_windowWidth, m_windowHeight, m_backbufferDC, 0, 0, SRCCOPY);
}

void CRendererGDI::DrawObject(CGameObject a_gameObject)
{

}


void CRendererGDI::End()
{

}


void CRendererGDI::Shutdown()
{

}