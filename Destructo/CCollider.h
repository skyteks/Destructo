#pragma once
#include "IComponent.h"
#include "SBCircle.h"
#include "SAABB.h"
#include "EColliderType.h"

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

    EColliderType GetType() const;

    void SetBCircle(const SBCircle a_BCircle);
    SBCircle GetBCircle() const;
    void SetAABB(const SAABB a_AABB);
    SAABB GetAABB() const;

private:
    SBCircle m_BCircle;
    SAABB m_AABB;
    EColliderType m_type;
};

