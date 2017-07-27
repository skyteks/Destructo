#include "CCollider.h"


CCollider::CCollider(SCircleBB a_circleBB)
    : m_circleBB(a_circleBB)
{
}

void CCollider::Update(CGameObject& a_object)
{
}

const SCircleBB CCollider::GetCircleBB() const
{
    return m_circleBB;
}
