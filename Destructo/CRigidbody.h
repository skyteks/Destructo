#pragma once
#include "IComponent.h"
#include "SVector3.h"
#include "CTime.h"
#include "CGameObject.h"

class CGameObject;
class IComponent;

class CRigidbody// : public IComponent
{
public:

    CRigidbody();

    static const SVector3 Gravity();

    void Update(CGameObject& a_object);

    const SVector3 GetVelocity() const;
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

