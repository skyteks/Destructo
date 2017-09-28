#include "SAABB.h"

SAABB::SAABB(SVector3 a_center, float a_halfWidths)
    : m_center(a_center)
    , m_halfWidths(a_halfWidths)
{
}


bool SAABB::ContainsPoint(SVector3 a_point) const
{
    SVector3 topLeft = SVector3(m_center.x - m_halfWidths, m_center.y - m_halfWidths);
    SVector3 bottomRight = SVector3(m_center.x + m_halfWidths, m_center.y + m_halfWidths);

    return topLeft.x <= a_point.x && topLeft.y <= a_point.x &&
        bottomRight.x >= a_point.x && bottomRight.y >= a_point.x;
}


bool SAABB::Intersects(SAABB a_other) const
{
    SVector3 topLeft = a_other.GetBorderPoint(0);
    SVector3 topRight = a_other.GetBorderPoint(1);
    SVector3 bottomLeft = a_other.GetBorderPoint(2);
    SVector3 bottomRight = a_other.GetBorderPoint(3);

    return ContainsPoint(topLeft) || ContainsPoint(topRight) || ContainsPoint(bottomLeft) || ContainsPoint(bottomRight);
}

SVector3 SAABB::GetBorderPoint(short a_index) const
{
    switch (a_index)
    {
    case 0:
        return SVector3(m_center.x - m_halfWidths, m_center.y - m_halfWidths, m_center.z);
    case 1:
        return SVector3(m_center.x - m_halfWidths, m_center.y + m_halfWidths, m_center.z);
    case 2:
        return SVector3(m_center.x + m_halfWidths, m_center.y - m_halfWidths, m_center.z);
    case 3:
        return SVector3(m_center.x + m_halfWidths, m_center.y + m_halfWidths, m_center.z);
    default:
        break;
    }
    return SVector3::Zero();
}
