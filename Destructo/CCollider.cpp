#include "CCollider.h"


CCollider::CCollider(CGameObject* a_owner)
    : IComponent(a_owner)
    , m_circleBB(SVector3::Zero(), 1.0f)
{
}

CCollider::~CCollider()
{
}


void CCollider::Initialize()
{
}


void CCollider::Update()
{
}


bool CCollider::AddRequiredComponents(IComponentManager* a_componentManager)
{
    return true;
}


void CCollider::SetCircleBB(const SCircleBB a_circleBB)
{
    m_circleBB = a_circleBB;
}

const SCircleBB CCollider::GetCircleBB() const
{
    return m_circleBB;
}
