#pragma once
#include "IComponent.h"
#include "SCircleBB.h"

class CGameObject;
class IComponent;

class CCollider// : public IComponent
{
public:
    CCollider(SCircleBB a_circleBB);

    void Update(CGameObject& a_object);
    const SCircleBB GetCircleBB() const;

private:
    SCircleBB m_circleBB;
};

