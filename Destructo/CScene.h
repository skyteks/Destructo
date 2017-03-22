#pragma once
#include <stdio.h>
#include <memory>

#include "IRenderer.h"
#include "CUIButton.h"
#include "CUISystem.h"
#include "GlobalFunctions.h"
#include "CInputManager.h"
#include "ISoundEngine.h"
#include "CTime.h"

class CScene
{
public:
	CScene();
	~CScene();

	bool Initialize(IRenderer* a_renderer);

	void Update();

	void Draw(IRenderer* a_renderer);

	void LoadButtons();

	void LoadTextures(IRenderer* a_renderer);

	void LoadSounds(ISoundEngine* a_soundEngine);

	void ReleaseTextures();

	void ReleaseSound(ISoundEngine* a_soundEngine);

	void Shutdown(ISoundEngine* a_soundEngine);

private:

	ITexture* m_backgroundTexture = nullptr;
	ITexture* m_terrainTexture = nullptr;
	ITexture* m_collisionTexture = nullptr;
	ITexture* m_playerTexture = nullptr;

	ITexture* m_buttonTexture = nullptr;
	ITexture* m_fontTexture = nullptr;

	void* m_testSound = nullptr;

	ButtonMap m_buttonMapButtonGDI;
	CUIButton m_uiButtonGDI;
	ButtonMap m_buttonMapButtonOpenGL;
	CUIButton m_uiButtonOpenGL;
	ButtonMap m_buttonMapButtonDirectX11;
	CUIButton m_uiButtonDirectX11;
	ButtonMap m_buttonMapButtonDirect2D;
	CUIButton m_uiButtonDirect2D;

	ISoundEngine* m_soundEngine = nullptr;

	int m_playerPosX = 800 / 2;
	int m_playerPosY = 600 / 2;

	float speed = 0;
};

