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
#include "CInputManager.h"

class CApplication
{
public:
	CApplication();
	~CApplication();

	bool Initialize(SRenderer::ERenderer currentRenderer, ISoundEngine* a_soundEngine, IInput* a_input);

	bool ChangeRenderer(SRenderer::ERenderer newRenderer);

	bool ChangeScene();

	void Run();

	void Shutdown();

	static LRESULT CALLBACK WndProc(HWND a_hwnd, unsigned int a_Message, WPARAM a_wParam, LPARAM a_lParam);

	bool Failed(HRESULT aResult);

	static bool engineRunning;
	static SRenderer::ERenderer currentRenderer;

	void SetSoundEngine(ISoundEngine* a_soundEngine);

private:
	SWindowDesc m_wndDesc = { "All Renderers TestEngine", 800, 600 };
	CWindow m_window;
	IRenderer* m_renderer = nullptr;
	CScene* m_scene = nullptr;
	HINSTANCE m_instance;
	POINT m_curserPos;
	ISoundEngine* m_soundEngine = nullptr;
	CGameTimer* m_timer = nullptr;
};

