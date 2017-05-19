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
#include "CQuadTree.h"
#include "SCircleBB.h"

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

	float speed = 0;

	CGameObject* m_objectPlayer;
	CGameObject* m_objectTerrain;
	CGameObject* m_objectBackground;
	CGameObject* m_objectPlayer2;

	CQuadTree* m_quadTree;
};

