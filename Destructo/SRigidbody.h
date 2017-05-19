#pragma once
#include "IComponent.h"
#include "SVector3.h"
#include "CTime.h"
#include "CGameObject.h"

class CGameObject;
class IComponent;

struct SRigidbody : public IComponent
{
public:

	SRigidbody();

	static SVector3 Gravity();

	void Update(CGameObject* a_object) override;

	SVector3 GetVelocity();
	void AddForce(SVector3 a_force);

	bool m_useGravity;
private:

	SVector3 m_force;
	float m_mass;
	float m_momentOfInertia;

	SVector3 m_velocity;
	float m_aceleration;
	float m_angularVelocity;
	float m_torque;

};

