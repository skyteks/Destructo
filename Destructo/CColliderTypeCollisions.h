#pragma once
#include "SAABB.h"
#include "SBCircle.h"

class CColliderTypeCollisions
{
public:
    static bool IntersectBoxBox(SAABB& a_AABB1, SAABB& a_AABB2);
    static bool IntersectCircleCircle(SBCircle& a_BCircle1, SBCircle& a_BCircle2);
    static bool IntersectBoxCircle(SAABB& a_AABB, SBCircle& a_BCircle);
    static bool IntersectCircleBox(SBCircle& a_BCircle, SAABB& a_AABB);

};

