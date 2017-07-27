#pragma once
#include "IComponent.h"
#include "SVector3.h"
#include "SMatrix4x4.h"

class CTransform : public IComponent
{
public:
    CTransform();
    CTransform(const SVector3& a_position, const SVector3& a_rotation = SVector3(0.0f, 0.0f, 0.0f), const SVector3& a_scale = SVector3(1.0f, 1.0f, 1.0f));
    virtual ~CTransform();

    void Start() override;
    void Update() override;
    bool AddRequiredComponents(IComponentManager* a_componentManager) override;


    const SVector3 GetPosition();
    const SVector3 GetRotation();
    const SVector3 GetScale();

    void SetPosition(SVector3& a_position);
    void SetRotation(SVector3& a_rotation);
    void SetScale(SVector3& a_scale);

    SMatrix4x4& GetWorld();
    const SVector3& GetForward();
    const SVector3& GetSide();
    const SVector3& GetUp();

private:

    void UpdateForwardSideUp();

    SVector3 m_position;
    SVector3 m_rotation;
    SVector3 m_scale;

    SVector3 m_forward;
    SVector3 m_side;
    SVector3 m_up;

    SMatrix4x4 m_world;
};

