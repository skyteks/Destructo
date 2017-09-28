#pragma once
#include "SVector3.h"

struct SBCircle
{
public:
    SBCircle(SVector3 a_center, float a_radius);

    bool ContainsPoint(SVector3 a_point) const;
    bool Intersects(SBCircle a_other) const;

    SVector3 m_center;
    float m_radius;
};

