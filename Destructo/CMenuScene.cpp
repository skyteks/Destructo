#include "CMenuScene.h"
#include "DataNames.h"

CMenuScene::CMenuScene()
{
}


CMenuScene::~CMenuScene()
{
}

bool CMenuScene::Initialize(IRenderer& a_renderer)
{
    CTextureManager::GetInstance().LoadTexture(TEXTURE_BUTTON);
    CTextureManager::GetInstance().LoadTexture(TEXTURE_FONT);
    CTextureManager::GetInstance().LoadTexture(TEXTURE_MENU);

    m_objectBackground = new CGameObject(SVector3(0.0f, 0.0f), SVector3(1.0f, 1.0f), 0.0f, TEXTURE_MENU, "");

    LoadButtons();
    return true;
}

void CMenuScene::Update()
{
    m_uiButtonGDI.UpdateState();
    m_uiButtonOpenGL.UpdateState();
    m_uiButtonDirectX11.UpdateState();
    m_uiButtonDirect2D.UpdateState();

    m_uiButtonGame.UpdateState();
}

void CMenuScene::Draw(IRenderer& a_renderer) const
{
    a_renderer.DrawObject(*m_objectBackground);

    a_renderer.DrawTexture(m_uiButtonGDI.GetDestination().x1, m_uiButtonGDI.GetDestination().y1, m_uiButtonGDI.GetDestination().x2, m_uiButtonGDI.GetDestination().y2, &m_uiButtonGDI.GetTexture(), m_uiButtonGDI.GetSource().x1, m_uiButtonGDI.GetSource().y1, m_uiButtonGDI.GetSource().x2, m_uiButtonGDI.GetSource().y2);
    a_renderer.DrawTexture(m_uiButtonOpenGL.GetDestination().x1, m_uiButtonOpenGL.GetDestination().y1, m_uiButtonOpenGL.GetDestination().x2, m_uiButtonOpenGL.GetDestination().y2, &m_uiButtonOpenGL.GetTexture(), m_uiButtonOpenGL.GetSource().x1, m_uiButtonOpenGL.GetSource().y1, m_uiButtonOpenGL.GetSource().x2, m_uiButtonOpenGL.GetSource().y2);
    a_renderer.DrawTexture(m_uiButtonDirectX11.GetDestination().x1, m_uiButtonDirectX11.GetDestination().y1, m_uiButtonDirectX11.GetDestination().x2, m_uiButtonDirectX11.GetDestination().y2, &m_uiButtonDirectX11.GetTexture(), m_uiButtonDirectX11.GetSource().x1, m_uiButtonDirectX11.GetSource().y1, m_uiButtonDirectX11.GetSource().x2, m_uiButtonDirectX11.GetSource().y2);
    a_renderer.DrawTexture(m_uiButtonDirect2D.GetDestination().x1, m_uiButtonDirect2D.GetDestination().y1, m_uiButtonDirect2D.GetDestination().x2, m_uiButtonDirect2D.GetDestination().y2, &m_uiButtonDirect2D.GetTexture(), m_uiButtonDirect2D.GetSource().x1, m_uiButtonDirect2D.GetSource().y1, m_uiButtonDirect2D.GetSource().x2, m_uiButtonDirect2D.GetSource().y2);

    auto fontTexture = CTextureManager::GetInstance().GetTextureByName(TEXTURE_FONT);

    a_renderer.DrawString(100 + 10, 530 + 10, "GDI", RGB(255, 0, 0), RGB(0, 0, 0), DT_TOP | DT_LEFT, fontTexture);
    a_renderer.DrawString(266 + 10, 530 + 10, "OpenGL", RGB(0, 255, 0), RGB(0, 0, 0), DT_TOP | DT_LEFT, fontTexture);
    a_renderer.DrawString(433 + 10, 530 + 10, "DirectX", RGB(0, 0, 255), RGB(0, 0, 0), DT_TOP | DT_LEFT, fontTexture);
    a_renderer.DrawString(600 + 10, 530 + 10, "Direct2D", RGB(0, 0, 255), RGB(0, 0, 0), DT_TOP | DT_LEFT, fontTexture);

    a_renderer.DrawTexture(m_uiButtonGame.GetDestination().x1, m_uiButtonGame.GetDestination().y1, m_uiButtonGame.GetDestination().x2, m_uiButtonGame.GetDestination().y2, &m_uiButtonGame.GetTexture(), m_uiButtonGame.GetSource().x1, m_uiButtonGame.GetSource().y1, m_uiButtonGame.GetSource().x2, m_uiButtonGame.GetSource().y2);
    a_renderer.DrawString(270 + 12, 370 + 10, "Start Game", RGB(0, 0, 255), RGB(0, 0, 0), DT_TOP | DT_LEFT, fontTexture);

    char buffer[200] = {};
    sprintf_s(buffer, "MouseX: %i\nMouseY: %i\nMouseL: %s\nMouseR: %s\nFPS: %i",
        CMouse::x,
        CMouse::y,
        CMouse::isLeftMouseDown ? "true" : "false",
        CMouse::isRightMouseDown ? "true" : "false",
        static_cast<int>(1 / CTime::GetInstance().DeltaTime())
    );
    a_renderer.DrawString(10, 10, buffer, RGB(255, 255, 255), RGB(0, 0, 0), DT_TOP | DT_LEFT, fontTexture);
}

void CMenuScene::Shutdown()
{
    SafeDelete(m_objectBackground);
}

void CMenuScene::LoadButtons()
{
    auto buttonTexture = CTextureManager::GetInstance().GetTextureByName(TEXTURE_BUTTON);

    m_buttonMapButtonGame.insert(ButtonPair(EButtonState::OnNormal, SButtonData{ 0, 0, 127, 38, nullptr }));
    m_buttonMapButtonGame.insert(ButtonPair(EButtonState::OnHover, SButtonData{ 0, 40, 127, 38, nullptr }));
    m_buttonMapButtonGame.insert(ButtonPair(EButtonState::OnPress, SButtonData{ 0, 80, 127, 38, CUISystem::EventHandler_OnPressButtonGame }));
    m_uiButtonGame = CUIButton(buttonTexture, { 270, 370, 200, 38 }, m_buttonMapButtonGame);

    m_buttonMapButtonGDI.insert(ButtonPair(EButtonState::OnNormal, SButtonData{ 0, 0, 127, 38, nullptr })); // x,y,width,height from source
    m_buttonMapButtonGDI.insert(ButtonPair(EButtonState::OnHover, SButtonData{ 0, 40, 127, 38, nullptr })); // x,y,width,height from source
    m_buttonMapButtonGDI.insert(ButtonPair(EButtonState::OnPress, SButtonData{ 0, 80, 127, 38, CUISystem::EventHandler_OnPressButtonGDI })); // x,y,width,height from source
    m_uiButtonGDI = CUIButton(buttonTexture, { 100, 530, 150, 38 }, m_buttonMapButtonGDI); // x, y, width, height for dest

    m_buttonMapButtonOpenGL.insert(ButtonPair(EButtonState::OnNormal, SButtonData{ 0, 0, 127, 38, nullptr })); // m_x,y,width,height from source
    m_buttonMapButtonOpenGL.insert(ButtonPair(EButtonState::OnHover, SButtonData{ 0, 40, 127, 38, nullptr })); // m_x,y,width,height from source
    m_buttonMapButtonOpenGL.insert(ButtonPair(EButtonState::OnPress, SButtonData{ 0, 80, 127, 38, CUISystem::EventHandler_OnPressButtonOpenGL })); // x,y,width,height from source
    m_uiButtonOpenGL = CUIButton(buttonTexture, { 266, 530, 150, 38 }, m_buttonMapButtonOpenGL); // x, y, width, height for dest

    m_buttonMapButtonDirectX11.insert(ButtonPair(EButtonState::OnNormal, SButtonData{ 0, 0, 127, 38, nullptr })); // x,y,width,height from source
    m_buttonMapButtonDirectX11.insert(ButtonPair(EButtonState::OnHover, SButtonData{ 0, 40, 127, 38, nullptr })); // x,y,width,height from source
    m_buttonMapButtonDirectX11.insert(ButtonPair(EButtonState::OnPress, SButtonData{ 0, 80, 127, 38, CUISystem::EventHandler_OnPressButtonDirectX11 })); // x,y,width,height from source
    m_uiButtonDirectX11 = CUIButton(buttonTexture, { 433, 530, 150, 38 }, m_buttonMapButtonDirectX11); // x, y, width, height for dest

    m_buttonMapButtonDirect2D.insert(ButtonPair(EButtonState::OnNormal, SButtonData{ 0, 0, 127, 38, nullptr })); // x,y,width,height from source
    m_buttonMapButtonDirect2D.insert(ButtonPair(EButtonState::OnHover, SButtonData{ 0, 40, 127, 38, nullptr })); // x,y,width,height from source
    m_buttonMapButtonDirect2D.insert(ButtonPair(EButtonState::OnPress, SButtonData{ 0, 80, 127, 38, CUISystem::EventHandler_OnPressButtonDirect2D })); // x,y,width,height from source
    m_uiButtonDirect2D = CUIButton(buttonTexture, { 600, 530, 150, 38 }, m_buttonMapButtonDirect2D); // x, y, width, height for dest
}