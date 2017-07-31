#include "CTransform.h"


CTransform::CTransform(CGameObject* a_owner)
    : IComponent(a_owner)
    , m_position(SVector3::Zero())
    , m_rotation(SVector3::Zero())
    , m_scale(SVector3::One())
    , m_forward(SVector3::Zero())
    , m_up(SVector3::Zero())
    , m_side(SVector3::Zero())
    , m_world(SMatrix4x4::Identity())
{
    UpdateForwardSideUp();
}

CTransform::~CTransform()
{
}

void CTransform::Initialize()
{
}

void CTransform::Update()
{
    GetWorld();
}

bool CTransform::AddRequiredComponents(IComponentManager* a_componentManager)
{
    return true;
}

const SVector3 CTransform::GetPosition()
{
    return m_position;
}

const SVector3 CTransform::GetRotation()
{
    return m_rotation;
}

const SVector3 CTransform::GetScale()
{
    return m_scale;
}


void CTransform::SetPosition(SVector3& a_position)
{
    m_position = a_position;
}


void CTransform::SetRotation(SVector3& a_rotation)
{
    m_rotation = a_rotation;

    UpdateForwardSideUp();
}


void CTransform::SetScale(SVector3& a_scale)
{
    m_scale = a_scale;
}

SMatrix4x4& CTransform::GetWorld()
{
    // translation
    auto translation = SMatrix4x4::Translation(m_position);
    // rotation
    auto rotation = SMatrix4x4::RotationX(m_rotation.x) * SMatrix4x4::RotationY(m_rotation.y) * SMatrix4x4::RotationZ(m_rotation.z);
    // scaling
    auto scaling = SMatrix4x4::Scale(m_scale);

    m_world = SMatrix4x4::Transpose(rotation * scaling * translation);

    return m_world;
}

const SVector3& CTransform::GetForward()
{
    return m_forward;
}

const SVector3& CTransform::GetSide()
{
    return m_side;
}

const SVector3& CTransform::GetUp()
{
    return m_up;
}

void CTransform::UpdateForwardSideUp()
{
    // update look/up/side
    SMatrix4x4 rotation = SMatrix4x4::RotationX(m_rotation.x) * SMatrix4x4::RotationX(m_rotation.y) * SMatrix4x4::RotationX(m_rotation.z);

    // extract look from rotation matrix
    m_forward.x = rotation.m13;
    m_forward.y = rotation.m23;
    m_forward.z = rotation.m33;

    // extract up from rotation matrix
    m_up.x = rotation.m12;
    m_up.y = rotation.m22;
    m_up.z = rotation.m32;

    // calculate side
    m_side = SVector3::Cross(m_forward, m_up);
}