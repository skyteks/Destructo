#pragma once
#include "IScene.h"
#include "CUIButton.h"
#include "CUISystem.h"
#include "CTextureManager.h"
#include "CMouse.h"
#include "CTime.h"

class CMenuScene : public IScene
{
public:
    CMenuScene();

    ~CMenuScene();
    bool Initialize(IRenderer& a_renderer) override;

    void Update() override;

    void Draw(IRenderer& a_renderer) const override;

    void Shutdown() override;

    void LoadButtons();

private:

    CGameObject* m_objectBackground;

    ButtonMap m_buttonMapButtonGame;
    CUIButton m_uiButtonGame;

    ButtonMap m_buttonMapButtonGDI;
    CUIButton m_uiButtonGDI;
    ButtonMap m_buttonMapButtonOpenGL;
    CUIButton m_uiButtonOpenGL;
    ButtonMap m_buttonMapButtonDirectX11;
    CUIButton m_uiButtonDirectX11;
    ButtonMap m_buttonMapButtonDirect2D;
    CUIButton m_uiButtonDirect2D;
};

