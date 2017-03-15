#include "CRendererGDI.h"

CRendererGDI::CRendererGDI()
{

}


CRendererGDI::~CRendererGDI()
{

}


bool CRendererGDI::InitializeGraphics(HWND a_hwnd)
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

ITexture* CRendererGDI::LoadTextureFromFile(char* a_path)
{
	return new CTextureGDI(a_path);
}


void CRendererGDI::DrawTexture(int a_posX, int a_posY, int a_width, int a_height, ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight)
{
	CTextureGDI* image = (CTextureGDI*)a_texture;

	TransparentBlt(m_backbufferDC, a_posX, a_posY, a_width, a_height, image->GetBitmapDeviceContect(), a_imgX, a_imgY, a_imgWidth, a_imgHeight, RGB(255, 0, 255));
}


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

			source.m_x1 = (c % 16) * 16;
			source.m_y1 = (c / 16) * 16;
			source.m_x2 = 16;
			source.m_y2 = 16;

			dest.m_x1 = a_posX + counter * 16;
			dest.m_y1 = a_posY + (newLines * 16);
			dest.m_x2 = 16;
			dest.m_y2 = 16;

			if (c == '\n')
			{
				newLines++;
				counter = 0;
			}
			else
			{
				DrawTexture(dest.m_x1, dest.m_y1, dest.m_x2, dest.m_y2, a_fontTexture, source.m_x1, source.m_y1, source.m_x2, source.m_y2);
				counter++;
			}
		}
	}
}


void CRendererGDI::Begin()
{
	BitBlt(m_windowDC, 0, 0, m_windowWidth, m_windowHeight, m_backbufferDC, 0, 0, SRCCOPY);
}


void CRendererGDI::End()
{

}


void CRendererGDI::ShutdownGraphics()
{

}