#include "CInputController.h"
#include "CTime.h"
#include "SVector3.h"

CInputController::CInputController(CGameObject* a_owner)
    : IComponent(a_owner)
    , m_keyUp(EKeyCode::W)
    , m_keyDown(EKeyCode::S)
    , m_keyLeft(EKeyCode::A)
    , m_keyRight(EKeyCode::D)
{
}


CInputController::~CInputController()
{
}


void CInputController::Initialize()
{
}


void CInputController::Update()
{
    float speed = 500 * CTime::GetInstance().DeltaTime();

    float playerPosX = 0.0f;
    float playerPosY = 0.0f;

    //if (m_objectPlayer->GetPosition().x < 800 - 32 && CInputManager::GetInstance().GetKey(EKeyCode::D))
    //    playerPosX += speed;
    //if (m_objectPlayer->GetPosition().x >= 0 && CInputManager::GetInstance().GetKey(EKeyCode::A))
    //    playerPosX -= speed;
    //if (m_objectPlayer->GetPosition().y < 600 - 32 && CInputManager::GetInstance().GetKey(EKeyCode::S))
    //    playerPosY += speed;
    //if (m_objectPlayer->GetPosition().y >= 0 && CInputManager::GetInstance().GetKey(EKeyCode::W))
    //    playerPosY -= speed;
    //
    //m_objectPlayer->SetPosition(m_objectPlayer->GetPosition() + SVector3(playerPosX, playerPosY));
    //
    //if (CInputManager::GetInstance().GetKey(EKeyCode::E))
    //{
    //    m_objectPlayer->AddRotation(CTime::GetInstance().DeltaTime());
    //}
    //if (CInputManager::GetInstance().GetKey(EKeyCode::Q))
    //{
    //    m_objectPlayer->AddRotation(-1.0f * CTime::GetInstance().DeltaTime());
    //}
    //
    //if (CInputManager::GetInstance().GetKey(EKeyCode::R))
    //{
    //    m_objectPlayer->SetScale(m_objectPlayer->GetScale() + SVector3::One() * CTime::GetInstance().DeltaTime());
    //}
    //if (CInputManager::GetInstance().GetKey(EKeyCode::F))
    //{
    //    m_objectPlayer->SetScale(m_objectPlayer->GetScale() - SVector3::One() * CTime::GetInstance().DeltaTime());
    //}
}

bool CInputController::AddRequiredComponents(IComponentManager* a_componentManager)
{
    return true;
}

void CInputController::SetMovementControlls(EKeyCode a_keyUp, EKeyCode a_keyDown, EKeyCode a_keyLeft, EKeyCode a_keyRight)
{
    m_keyUp = a_keyUp;
    m_keyDown = a_keyDown;
    m_keyLeft = a_keyLeft;
    m_keyRight = a_keyRight;
}
