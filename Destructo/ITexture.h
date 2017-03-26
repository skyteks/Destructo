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
};