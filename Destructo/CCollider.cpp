#include "CCollider.h"


CCollider::CCollider(CGameObject* a_owner)
    : IComponent(a_owner)
    , m_BCircle(SVector3::Zero(), 1.0f)
    , m_AABB(SVector3::Zero(), 1.0f)
    , m_type(EColliderType::BCirle)
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


EColliderType CCollider::GetType() const
{
    return m_type;
}


void CCollider::SetBCircle(const SBCircle a_BCircle)
{
    m_BCircle = a_BCircle;
    m_type = EColliderType::BCirle;
}


SBCircle CCollider::GetBCircle() const
{
    return m_BCircle;
}


void CCollider::SetAABB(const SAABB a_AABB)
{
    m_AABB = a_AABB;
    m_type = EColliderType::AABB;
}


SAABB CCollider::GetAABB() const
{
    return m_AABB;
}
