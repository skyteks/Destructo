#pragma once

#include "IInput.h"

class CInputMouseAndKeyboard : public IInput
{
public:
	CInputMouseAndKeyboard();

	~CInputMouseAndKeyboard();

	void InitializeInput(void* m_windowHandle);

	void Release();

	bool IsKeyPressed(int key);

	void Begin();

	void End();

private:

	HWND m_windowHandle;
	
	int mouseX;
	int mouseY;

	bool mousePressed[3];
};

