#pragma once
#include <stdio.h>
#include <memory>

#include "IRenderer.h"
#include "CUIButton.h"
#include "CUISystem.h"
#include "GlobalFunctions.h"
#include "CInputManager.h"
#include "CTime.h"
#include "CTextureManager.h"

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

	//void LoadSounds(ISoundEngine* a_soundEngine);

	void ReleaseTextures();

	//void ReleaseSound(ISoundEngine* a_soundEngine);

	void Shutdown();

private:

	//ITexture* m_backgroundTexture = nullptr;
	//ITexture* m_terrainTexture = nullptr;
	//ITexture* m_collisionTexture = nullptr;
	//ITexture* m_playerTexture = nullptr;

	//ITexture* m_buttonTexture = nullptr;
	//ITexture* m_fontTexture = nullptr;

	std::string m_backgroundTexture;
	std::string m_terrainTexture;
	std::string m_collisionTexture;
	std::string m_playerTexture;

	std::string m_buttonTexture;
	std::string m_fontTexture;

	void* m_testSound = nullptr;

	ButtonMap m_buttonMapButtonGDI;
	CUIButton m_uiButtonGDI;
	ButtonMap m_buttonMapButtonOpenGL;
	CUIButton m_uiButtonOpenGL;
	ButtonMap m_buttonMapButtonDirectX11;
	CUIButton m_uiButtonDirectX11;
	ButtonMap m_buttonMapButtonDirect2D;
	CUIButton m_uiButtonDirect2D;

	int m_playerPosX = 800 / 2;
	int m_playerPosY = 600 / 2;

	float speed = 0;
};

