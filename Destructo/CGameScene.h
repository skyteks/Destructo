#pragma once

#include "IScene.h"
#include "CQuadTree.h"

class CGameScene : public IScene
{
public:
    CGameScene();
    
    ~CGameScene() override;

    bool Initialize(IRenderer& a_renderer) override;

    void Update() override;

    void Draw(IRenderer& a_renderer) const override;

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

