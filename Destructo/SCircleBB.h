#pragma once
#include "SVector3.h"

struct SCircleBB
{
public:
	SCircleBB(SVector3 a_center, float a_radius);

	SVector3 GetCenter();
	float GetRadius();
	bool ContainsPoint(SVector3 a_point);
	bool Intersects(SCircleBB& a_other);


private:
	SVector3 m_center;
	float m_radius;
};

