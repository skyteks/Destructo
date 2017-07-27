#include "SAABB.h"

SAABB::SAABB(SVector3 a_center, float a_halfWidths)
    : m_center(a_center)
    , m_halfWidths(a_halfWidths)
{
}

SVector3 SAABB::GetCenter()
{
    return m_center;
}

float SAABB::GetHalfWidths()
{
    return m_halfWidths;
}

bool SAABB::ContainsPoint(SVector3 a_point)
{
    SVector3 topLeft = SVector3(m_center.x - m_halfWidths, m_center.y - m_halfWidths);
    SVector3 bottomRight = SVector3(m_center.x + m_halfWidths, m_center.y + m_halfWidths);

    return topLeft.x <= a_point.x && topLeft.y <= a_point.x &&
        bottomRight.x >= a_point.x && bottomRight.y >= a_point.x;
}

bool SAABB::intersectsAABB(SAABB a_other)
{
    SVector3 topLeft = SVector3(a_other.m_center.x - m_halfWidths, a_other.m_center.y - m_halfWidths);
    SVector3 topRight = SVector3(a_other.m_center.x - m_halfWidths, a_other.m_center.y + m_halfWidths);
    SVector3 bottomLeft = SVector3(a_other.m_center.x + m_halfWidths, a_other.m_center.y - m_halfWidths);
    SVector3 bottomRight = SVector3(a_other.m_center.x + m_halfWidths, a_other.m_center.y + m_halfWidths);

    return ContainsPoint(topLeft) || ContainsPoint(topRight) || ContainsPoint(bottomLeft) || ContainsPoint(bottomRight);
}
