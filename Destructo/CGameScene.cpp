#include "CGameScene.h"
#include <stdio.h>
#include <memory>
#include "CMouse.h"
#include "DataNames.h"
#include "CTextureManager.h"
#include "ITexture.h"
#include "CTransform.h"
#include "CSprite.h"
#include "CTime.h"
#include "CInputController.h"
#include "CRigidbody.h"

CGameScene::CGameScene()
    : m_objectPlayer(nullptr)
    , m_objectPlayer2(nullptr)
    , m_objectTerrain(nullptr)
    , m_objectBackground(nullptr)
{
}


CGameScene::~CGameScene()
{
}


bool CGameScene::Initialize(IRenderer& a_renderer)
{
    CTextureManager::GetInstance().LoadTexture(TEXTURE_TERRAIN);
    CTextureManager::GetInstance().LoadTexture(TEXTURE_COLLISION);
    CTextureManager::GetInstance().LoadTexture(TEXTURE_BACKGROUND);
    CTextureManager::GetInstance().LoadTexture(TEXTURE_PLAYER);
    //CTextureManager::GetInstance().LoadTexture(TEXTURE_PLAYER2);
    CTextureManager::GetInstance().LoadTexture(TEXTURE_FONT);

    //CRigidbody* playerRigid = new CRigidbody();
    //CCollider* playerCol = new CCollider(SBCircle(SVector3(0, 0), 100));
    //
    //CRigidbody* testRigid = new CRigidbody();
    //CCollider* testCol = new CCollider(SBCircle(SVector3(0, 0), 100));

    m_objectPlayer = new CGameObject((std::string)"Player1");
    m_objectPlayer->GetComponent<CTransform>()->SetPosition(SVector3(100.0f, 100.0f));
    m_objectPlayer->GetComponent<CTransform>()->SetRotation(SVector3(0.0f, 0.0f, 0.0f));
    m_objectPlayer->AddComponent<CSprite>(m_objectPlayer)->SetTextureName(TEXTURE_PLAYER);
    m_objectPlayer->AddComponent<CInputController>(m_objectPlayer)->SetMovementControlls(EKeyCode::W, EKeyCode::S, EKeyCode::A, EKeyCode::D);
    //m_objectPlayer->AddComponent<CRigidbody>(m_objectPlayer)->m_useGravity = true;

    //m_objectPlayer2 = new CGameObject((std::string)"Player2");
    //m_objectPlayer2->GetComponent<CTransform>()->SetPosition(SVector3(100.0f, 100.0f));
    //m_objectPlayer2->GetComponent<CTransform>()->SetRotation(SVector3(0.0f, 0.0f, 0.0f));
    //m_objectPlayer2->AddComponent<CSprite>(m_objectPlayer2)->SetTextureName(TEXTURE_PLAYER2);
    //m_objectPlayer2->AddComponent<CInputController>(m_objectPlayer2)->SetMovementControlls(EKeyCode::Up, EKeyCode::Down, EKeyCode::Left, EKeyCode::Right);

    m_objectTerrain = new CGameObject((std::string)"Terrain");
    m_objectTerrain->AddComponent<CSprite>(m_objectTerrain)->SetTextureName(TEXTURE_TERRAIN);
    m_objectTerrain->GetComponent<CSprite>()->SetOpacityMaskName(TEXTURE_COLLISION);

    m_objectBackground = new CGameObject((std::string)"Background");
    m_objectBackground->AddComponent<CSprite>(m_objectBackground)->SetTextureName(TEXTURE_BACKGROUND);

    return true;
}


void CGameScene::Update()
{
    if (CMouse::isLeftMouseDown)
    {
        CTextureManager::GetInstance().GetTextureByName(TEXTURE_COLLISION)->SetPixel(CMouse::x, CMouse::y, 0xFF000000);
    }

    m_objectPlayer->GetComponent<CInputController>()->Update();

    //m_objectPlayer->GetComponent<CRigidbody>()->Update();
    //m_objectPlayer2->GetComponent<CRigidbody>()->Update();
}


void CGameScene::Draw(IRenderer& a_renderer) const
{
    auto fontTexture = CTextureManager::GetInstance().GetTextureByName(TEXTURE_FONT);

    //a_renderer.DrawTexture(0, 0, 800, 600, backgroundTexture, 0, 0, backgroundTexture->GetWidth(), backgroundTexture->GetHeight());
    a_renderer.DrawObject(*m_objectBackground);
    //a_renderer.DrawTextureWithOpacityMask(0, 0, 800, 600, terrainTexture, 0, 0, terrainTexture->GetWidth(), terrainTexture->GetHeight(), collisionTexture);
    a_renderer.DrawObject(*m_objectTerrain);
    //a_renderer.DrawTexture(m_playerPosX, m_playerPosY, 32, 32, playerTexture, 0, 0, playerTexture->GetWidth(), playerTexture->GetHeight());
    a_renderer.DrawObject(*m_objectPlayer);

    //a_renderer.DrawObject(*m_objectPlayer2);

    char buffer[200] = {};
    sprintf_s(buffer, "MouseX: %i\nMouseY: %i\nMouseL: %s\nMouseR: %s\nFPS: %i\nRenderer: %s\nPlayerPos: %f %f \n",
        CMouse::x,
        CMouse::y,
        CMouse::isLeftMouseDown ? "true" : "false",
        CMouse::isRightMouseDown ? "true" : "false",
        static_cast<int>(1 / CTime::GetInstance().DeltaTime()),
        RendererTypeToString(a_renderer.GetRendererType()),
        m_objectPlayer->GetComponent<CTransform>()->GetPosition().x,
        m_objectPlayer->GetComponent<CTransform>()->GetPosition().y);
    a_renderer.DrawString(10, 10, buffer, RGB(255, 255, 255), RGB(0, 0, 0), DT_TOP | DT_LEFT, fontTexture);
}


void CGameScene::Shutdown()
{
    SafeDelete(m_objectPlayer);
    SafeDelete(m_objectTerrain);
    SafeDelete(m_objectBackground);
    SafeDelete(m_objectPlayer2);
}
