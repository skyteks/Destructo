#pragma once

#include <Windows.h>
#include <windowsx.h>

#include "CRendererGDI.h"
#include "CRendererOpenGL.h"
#include "CRendererDirectX11.h"
#include "CWindow.h"
#include "IRenderer.h"
#include "CMouse.h"
#include "CScene.h"
#include "ISoundEngine.h"

class CApplication
{
public:
	CApplication();
	~CApplication();

	bool InitializeApplication(SRenderer::ERenderer currentRenderer, ISoundEngine* a_soundEngine);

	bool ChangeRenderer(SRenderer::ERenderer newRenderer);

	bool ChangeScene();

	void Run();

	static LRESULT CALLBACK WndProc(HWND a_hwnd, unsigned int a_Message, WPARAM a_wParam, LPARAM a_lParam);

	bool Failed(HRESULT aResult);

	static bool engineRunning;
	static SRenderer::ERenderer currentRenderer;

  void SetSoundEngine(ISoundEngine* a_soundEngine);

private:
	SWindowDesc wndDesc = { "All Renderers TestEngine", 800, 600 };
	CWindow window;
	IRenderer* m_renderer = nullptr;
	CScene* m_scene = nullptr;
	HINSTANCE instance;
	POINT curserPos;

  ISoundEngine* m_soundEngine;
};

