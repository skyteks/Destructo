#include "CColliderTypeCollisions.h"

bool CColliderTypeCollisions::IntersectBoxBox(SAABB& a_AABB1, SAABB& a_AABB2)
{
    return a_AABB1.Intersects(a_AABB2);
}


bool CColliderTypeCollisions::IntersectCircleCircle(SBCircle& a_BCircle1, SBCircle& a_BCircle2)
{
    return a_BCircle1.Intersects(a_BCircle2);
}


bool CColliderTypeCollisions::IntersectBoxCircle(SAABB& a_AABB, SBCircle& a_BCircle)
{
    return IntersectCircleBox(a_BCircle, a_AABB);
}


bool CColliderTypeCollisions::IntersectCircleBox(SBCircle& a_BCircle, SAABB& a_AABB)
{
    SVector3 topLeft = a_AABB.GetBorderPoint(0);
    SVector3 topRight = a_AABB.GetBorderPoint(1);
    SVector3 bottomLeft = a_AABB.GetBorderPoint(2);
    SVector3 bottomRight = a_AABB.GetBorderPoint(3);

    return a_BCircle.ContainsPoint(topLeft) || a_BCircle.ContainsPoint(topRight) || a_BCircle.ContainsPoint(bottomLeft) || a_BCircle.ContainsPoint(bottomRight);
}
