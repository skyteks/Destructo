#include "CTextureGDI.h"



CTextureGDI::CTextureGDI(std::string a_path)
{
	m_bitmapHandle = (HBITMAP)LoadImage(GetModuleHandle(NULL), a_path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	BITMAP bitmap;

	GetObject(m_bitmapHandle, sizeof(bitmap), &bitmap);

	m_width = bitmap.bmWidth;
	m_height = bitmap.bmHeight;

	m_bitmapDC = CreateCompatibleDC(NULL);
	
	SelectObject(m_bitmapDC, m_bitmapHandle);
}


CTextureGDI::~CTextureGDI()
{
	DeleteDC(m_bitmapDC);
}

int CTextureGDI::GetWidth() const
{
	return m_width;
}

int CTextureGDI::GetHeight() const
{
	return m_height;
}

HBITMAP CTextureGDI::GetBitmapHandle() const
{
	return m_bitmapHandle;
}

HDC CTextureGDI::GetBitmapDeviceContect() const
{
	return m_bitmapDC;
}

int CTextureGDI::GetPitch() const
{
	return m_pitch;
}

int CTextureGDI::GetBPP() const
{
	return m_bitsPerPixel;
}

void CTextureGDI::SetPixel(int a_x, int a_y, int a_color)
{
}
