#pragma once

#include <Windows.h>
#include <windowsx.h>

#include "CRendererGDI.h"
#include "CRendererOpenGL.h"
#include "CRendererDirectX11.h"
#include "CRendererDirect2D.h"
#include "CWindow.h"
#include "IRenderer.h"
#include "ERenderer.h"
#include "CMouse.h"
#include "EScenes.h"
#include "CGameScene.h"
#include "CMenuScene.h"
#include "CAudio.h"
#include "CInputManager.h"
#include "CTime.h"
#include "CTextureManager.h"

class CApplication
{
public:
	CApplication();

	~CApplication();

	bool Initialize(ERenderer a_currentRenderer, IAudio* a_soundEngine, IInput* a_input);

	bool ChangeRenderer(ERenderer a_newRenderer);

	bool ChangeScene(EScenes a_newScene);

	void Run();

	void Shutdown();

	static LRESULT CALLBACK WndProc(HWND a_hwnd, uint32_t a_Message, WPARAM a_wParam, LPARAM a_lParam);

	bool Failed(HRESULT aResult);

	static bool engineRunning;
	static ERenderer currentRenderer;

	void SetSoundEngine(IAudio* a_soundEngine);

private:
	SWindowDesc m_wndDesc = { "Destructo", 800, 600 };
	CWindow m_window;
	IRenderer* m_renderer = nullptr;
	IScene* m_scene = nullptr;
	HINSTANCE m_instance;
	POINT m_curserPos;
	IAudio* m_soundEngine = nullptr;
};

