#pragma once

#include <Windows.h>
#include <string>

class CApplication;

struct SWindowDesc
{
	std::string WindowName;
	int x2;
	int y2;
};

class CWindow
{

public:
	CWindow();
	~CWindow();

	HWND GetWindowHandle();

	bool Initialize(const SWindowDesc& a_windowDesc, CApplication* a_application);

private:
	HWND m_hwnd;

};

