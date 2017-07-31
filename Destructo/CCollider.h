#pragma once
#include "IComponent.h"
#include "SCircleBB.h"

class CGameObject;
class IComponent;

class CCollider : public IComponent
{
public:
    CCollider(CGameObject* a_owner);
    virtual ~CCollider();

    void Initialize();
    void Update() override;
    bool AddRequiredComponents(IComponentManager* a_componentManager) override;

    void SetCircleBB(const SCircleBB a_circleBB);
    const SCircleBB GetCircleBB() const;

private:
    SCircleBB m_circleBB;
};

