#include "CTextureGDI.h"



CTextureGDI::CTextureGDI(char* a_path)
{
	bitmapHandle = (HBITMAP)LoadImage(GetModuleHandle(NULL), a_path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	BITMAP bitmap;

	GetObject(bitmapHandle, sizeof(bitmap), &bitmap);

	m_width = bitmap.bmWidth;
	m_height = bitmap.bmHeight;

	m_bitmapDC = CreateCompatibleDC(NULL);
	
	SelectObject(m_bitmapDC, bitmapHandle);
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
	return bitmapHandle;
}

HDC CTextureGDI::GetBitmapDeviceContect()
{
	return m_bitmapDC;
}
