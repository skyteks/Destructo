#include "SCircleBB.h"



SCircleBB::SCircleBB(SVector3 a_center, float a_radius)
    : m_center(a_center)
    , m_radius(a_radius)
{
}

const SVector3& SCircleBB::GetCenter() const
{
    return m_center;
}

float SCircleBB::GetRadius() const
{
    return m_radius;
}

bool SCircleBB::ContainsPoint(const SVector3 a_point) const
{
    return SVector3::Distance(m_center, a_point) <= m_radius;
}

bool SCircleBB::Intersects(const SCircleBB a_other) const
{
    return SVector3::Distance(m_center, a_other.GetCenter()) <= m_radius + a_other.GetRadius();
}