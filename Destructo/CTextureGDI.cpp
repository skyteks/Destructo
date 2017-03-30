#include "CTextureGDI.h"



CTextureGDI::CTextureGDI(const char* a_path)
{
	m_bitmapHandle = (HBITMAP)LoadImage(GetModuleHandle(NULL), a_path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

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

int CTextureGDI::GetWidth()
{
	return m_width;
}

int CTextureGDI::GetHeight()
{
	return m_height;
}

HBITMAP CTextureGDI::GetBitmapHandle()
{
	return m_bitmapHandle;
}

HDC CTextureGDI::GetBitmapDeviceContect()
{
	return m_bitmapDC;
}

int CTextureGDI::GetPitch()
{
	return m_pitch;
}

int CTextureGDI::GetBPP()
{
	return m_bitsPerPixel;
}

void CTextureGDI::SetPixel(int a_x, int a_y, int a_color)
{
}
