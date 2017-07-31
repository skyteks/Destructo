#pragma once
#include "IComponent.h"
#include "IComponentManager.h"
#include "CInputManager.h"

class CInputController : public IComponent
{
public:
    CInputController(CGameObject* a_owner);
    virtual ~CInputController();

    void Initialize() override;
    void Update() override;
    bool AddRequiredComponents(IComponentManager* a_componentManager) override;

    void SetMovementControlls(EKeyCode a_keyUp, EKeyCode a_keyDown, EKeyCode a_keyLeft, EKeyCode a_keyRight);
private:
    EKeyCode m_keyUp;
    EKeyCode m_keyDown;
    EKeyCode m_keyLeft;
    EKeyCode m_keyRight;
};

