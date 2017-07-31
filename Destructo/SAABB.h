#pragma once
#include "SVector3.h"

struct SAABB
{
public:
    SAABB(SVector3 a_center, float a_halfWidths);

    bool ContainsPoint(SVector3 a_point) const;
    bool intersectsAABB(SAABB a_other) const;

    SVector3 m_center;
    float m_halfWidths;
};

