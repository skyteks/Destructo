#include "SRigidbody.h"


SRigidbody::SRigidbody()
	: m_useGravity(true)
	, m_force(SVector3::Zero())
	, m_mass(1.0f)
	, m_momentOfInertia(0.0f)
	, m_velocity(SVector3::Zero())
	, m_aceleration(0.0f)
	, m_angularVelocity(0.0f)
	, m_torque(0.0f)
{
}

SVector3 SRigidbody::Gravity()
{
	return SVector3(0.0f, 9.81f * 0.1f);
}

void SRigidbody::Update(CGameObject* a_object)
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
	a_object->SetPosition(a_object->GetPosition() + m_velocity * dt);
	a_object->AddRotation(m_angularVelocity * dt);
}

SVector3 SRigidbody::GetVelocity()
{
	return m_velocity;
}

void SRigidbody::AddForce(SVector3 a_force)
{
	m_force += a_force;
}
