#include "SCircleBB.h"



SCircleBB::SCircleBB(SVector3 a_center, float a_radius)
	: m_center(a_center)
	, m_radius(a_radius)
{
}

SVector3 SCircleBB::GetCenter()
{
	return m_center;
}

float SCircleBB::GetRadius()
{
	return m_radius;
}

bool SCircleBB::ContainsPoint(SVector3 a_point)
{
	return SVector3::Distance(m_center, a_point) <= m_radius;
}

bool SCircleBB::Intersects(SCircleBB& a_other)
{
	return SVector3::Distance(m_center, a_other.GetCenter()) <= m_radius + a_other.GetRadius();
}
