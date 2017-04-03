#pragma once
#include <stdio.h>
#include <memory>

#include "IScene.h"

#include "GlobalFunctions.h"
#include "CInputManager.h"
#include "CMouse.h"
#include "CTime.h"
#include "CTextureManager.h"
#include "CGameObject.h"

class CGameScene : public IScene
{
public:
	CGameScene();

	~CGameScene() override;

	bool Initialize(IRenderer* a_renderer) override;

	void Update() override;

	void Draw(IRenderer* a_renderer) override;

	

	void Shutdown() override;

private:

	void* m_testSound = nullptr;

	

	int m_playerPosX = 800 / 2;
	int m_playerPosY = 600 / 2;

	float speed = 0;

	CGameObject* m_objectPlayer;
	CGameObject* m_objectTerrain;
	CGameObject* m_objectBackground;
};

