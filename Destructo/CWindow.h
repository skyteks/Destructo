#pragma once

#include <Windows.h>
#include <string>

class CApplication;

struct SWindowDesc
{
	std::string WindowName;
	int m_width;
	int m_height;
};

class CWindow
{

public:
	CWindow();
	~CWindow();

	HWND GetWindowHandle();

	bool InitializeWindow(const SWindowDesc& a_windowDesc, CApplication* a_application);

private:
	HWND m_hwnd;

};

