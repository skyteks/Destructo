#include "SBCircle.h"


SBCircle::SBCircle(SVector3 a_center, float a_radius)
    : m_center(a_center)
    , m_radius(a_radius)
{
}


bool SBCircle::ContainsPoint(const SVector3 a_point) const
{
    return SVector3::Distance(m_center, a_point) <= m_radius;
}


bool SBCircle::Intersects(const SBCircle a_other) const
{
    return SVector3::Distance(m_center, a_other.m_center) <= m_radius + a_other.m_radius;
}
