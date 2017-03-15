#pragma once

#include <windows.h>

class ITexture
{
public:
	virtual ~ITexture(){}

	virtual int GetWidth() = 0;

	virtual int GetHeight() = 0;
};