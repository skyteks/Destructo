#pragma once
#include "IComponent.h"
#include "IComponentManager.h"
#include "SVector3.h"

class CRigidbody : public IComponent
{
public:

    CRigidbody(CGameObject* a_owner);
    virtual ~CRigidbody();

    void Initialize() override;
    void Update() override;
    bool AddRequiredComponents(IComponentManager * a_componentManager) override;
    
    static const SVector3 Gravity();

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

