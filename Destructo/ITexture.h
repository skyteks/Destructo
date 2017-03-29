#pragma once
#include <Windows.h>
class ITexture
{
public:
	virtual ~ITexture(){}

	virtual int GetWidth() = 0;

	virtual int GetHeight() = 0;

	virtual int GetPitch() = 0;

	virtual int GetBPP() = 0;

	virtual void SetPixel(int a_x, int a_y, int a_color) = 0;
};