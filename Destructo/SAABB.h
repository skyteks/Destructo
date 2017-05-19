#pragma once
#include "SVector3.h"

struct SAABB
{
public:
	SAABB(SVector3 a_center, float a_halfWidths);

	SVector3 GetCenter();
	float GetHalfWidths();
	bool ContainsPoint(SVector3 a_point);
	bool intersectsAABB(SAABB a_other);

private:
	SVector3 m_center;
	float m_halfWidths;
};

