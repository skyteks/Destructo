#include "CTextureGDI.h"



CTextureGDI::CTextureGDI(char* a_path)
{
	bitmapHandle = (HBITMAP)LoadImage(GetModuleHandle(NULL), a_path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	BITMAP bitmap;

	GetObject(bitmapHandle, sizeof(bitmap), &bitmap);

	x2 = bitmap.bmWidth;
	y2 = bitmap.bmHeight;

	m_bitmapDC = CreateCompatibleDC(NULL);
	
	SelectObject(m_bitmapDC, bitmapHandle);
}


CTextureGDI::~CTextureGDI()
{
	DeleteDC(m_bitmapDC);
}

int CTextureGDI::GetWidth()
{
	return x2;
}

int CTextureGDI::GetHeight()
{
	return y2;
}

HBITMAP CTextureGDI::GetBitmapHandle()
{
	return bitmapHandle;
}

HDC CTextureGDI::GetBitmapDeviceContect()
{
	return m_bitmapDC;
}
