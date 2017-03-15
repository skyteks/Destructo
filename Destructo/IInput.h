#pragma once

#include "CWindow.h"

class IInput
{
public:
	virtual void InitializeInput(void* m_windowHandle) = 0;

	virtual void Release() = 0;

	virtual bool IsKeyPressed(int key) = 0;

	virtual void Begin() = 0;

	virtual void End() = 0;
};