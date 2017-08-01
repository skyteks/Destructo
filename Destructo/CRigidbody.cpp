#include "CRigidbody.h"
#include "CTime.h"
#include "CTransform.h"
#include "CGameObject.h"

CRigidbody::CRigidbody(CGameObject* a_owner)
    : IComponent(a_owner)
    , m_useGravity(true)
    , m_force(SVector3::Zero())
    , m_mass(1.0f)
    , m_momentOfInertia(0.0f)
    , m_velocity(SVector3::Zero())
    , m_aceleration(0.0f)
    , m_angularVelocity(0.0f)
    , m_torque(0.0f)
{
}

CRigidbody::~CRigidbody()
{
}


const SVector3 CRigidbody::Gravity()
{
    return SVector3(0.0f, 9.81f * 0.1f);
}


void CRigidbody::Initialize()
{
}


void CRigidbody::Update()
{
    float dt = CTime::GetInstance().DeltaTime();
    if (m_useGravity)
    {
        m_force = (1.0f / m_mass * Gravity()) * dt;
    }
    m_velocity += m_force;
    if (m_momentOfInertia != 0.0f)
    {
        m_angularVelocity += m_torque * (1.0f / m_momentOfInertia) * dt;
    }
    CTransform* transform = m_owner->GetComponent<CTransform>();
    transform->AddPosition(m_velocity * dt);
    transform->AddRotation(SVector3::Forward() * m_angularVelocity * dt);
}


bool CRigidbody::AddRequiredComponents(IComponentManager* a_componentManager)
{
    return true;
}


const SVector3 CRigidbody::GetVelocity() const
{
    return m_velocity;
}


void CRigidbody::AddForce(SVector3 a_force)
{
    m_force += a_force;
}