#pragma once
#include <Windows.h>
class ITexture
{
public:
	virtual ~ITexture(){}

	virtual int GetWidth() const = 0;

	virtual int GetHeight() const = 0;

	virtual int GetPitch() const = 0;

	virtual int GetBPP() const = 0;

	virtual void SetPixel(int a_x, int a_y, int a_color) = 0;
};