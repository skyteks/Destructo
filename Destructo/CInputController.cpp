#include "CInputController.h"
#include "CTime.h"
#include "SVector3.h"
#include "CGameObject.h"
#include "CTransform.h"

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

    CTransform* transform = m_owner->GetComponent<CTransform>();
    if (transform->GetPosition().x < 800 - 32 && CInputManager::GetInstance().GetKey(m_keyRight))
        playerPosX += speed;
    if (transform->GetPosition().x >= 0 && CInputManager::GetInstance().GetKey(m_keyLeft))
        playerPosX -= speed;
    if (transform->GetPosition().y < 600 - 32 && CInputManager::GetInstance().GetKey(m_keyDown))
        playerPosY += speed;
    if (transform->GetPosition().y >= 0 && CInputManager::GetInstance().GetKey(m_keyUp))
        playerPosY -= speed;

    transform->AddPosition(SVector3(playerPosX, playerPosY));

    if (CInputManager::GetInstance().GetKey(EKeyCode::E))
    {
        transform->AddRotation(SVector3::Forward() * CTime::GetInstance().DeltaTime());
    }
    if (CInputManager::GetInstance().GetKey(EKeyCode::Q))
    {
        transform->AddRotation(SVector3::Backward() * CTime::GetInstance().DeltaTime());
    }
    
    if (CInputManager::GetInstance().GetKey(EKeyCode::R))
    {
        transform->SetScale(transform->GetScale() + SVector3::One() * CTime::GetInstance().DeltaTime());
    }
    if (CInputManager::GetInstance().GetKey(EKeyCode::F))
    {
        transform->SetScale(transform->GetScale() - SVector3::One() * CTime::GetInstance().DeltaTime());
    }
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
