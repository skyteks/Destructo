#pragma once
#include "SVector3.h"

struct SCircleBB
{
public:
    SCircleBB(SVector3 a_center, float a_radius);

    bool ContainsPoint(SVector3 a_point) const;
    bool Intersects(SCircleBB a_other) const;

    SVector3 m_center;
    float m_radius;
};

