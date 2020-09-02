#pragma once
#include "SVector3.h"

struct SAABB
{
public:
    SAABB(SVector3 a_center, float a_halfWidths);
    SAABB(SVector3 a_topLeft, SVector3 a_size);

    bool ContainsPoint(SVector3 a_point) const;
    bool Intersects(SAABB a_other) const;
    SVector3 GetBorderPoint(short a_index) const;

    SVector3 m_center;
    float m_halfWidths;
};

