#pragma once
#include <stdio.h>
#include <memory>

#include "IRenderer.h"
#include "CUIButton.h"
#include "CUISystem.h"
#include "GlobalFunctions.h"

class CScene
{
public:
	CScene();
	~CScene();

	bool InitializeScene(IRenderer* a_renderer);

	void Update();

	void Draw(IRenderer* a_renderer);

	void LoadButtons();

	void LoadTextures(IRenderer* a_renderer);

	void ReleaseTextures();

	void ShutdownScene();

private:

	ITexture* m_backgroundTexture = nullptr;
	ITexture* m_terrainTexture = nullptr;
	ITexture* m_collisionTexture = nullptr;
	ITexture* m_playerTexture = nullptr;

	ITexture* m_buttonTexture = nullptr;
	ITexture* m_fontTexture = nullptr;

	ButtonMap m_buttonMapButtonGDI;
	CUIButton m_uiButtonGDI;
	ButtonMap m_buttonMapButtonOpenGL;
	CUIButton m_uiButtonOpenGL;
	ButtonMap m_buttonMapButtonDirectX11;
	CUIButton m_uiButtonDirectX11;

	int m_playerPosX = 0;
	int m_playerPosY = 0;
};

