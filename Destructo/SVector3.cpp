#include "SVector3.h"
#include <math.h>
#include <limits>

SVector3::SVector3()
    : x(0.0f), y(0.0f), z(0.0f)
{
}


SVector3::SVector3(float a_x, float a_y, float a_z)
    : x(a_x), y(a_y), z(a_z)
{
}


SVector3 SVector3::Normalized() const
{
    float length = Magnitude();
    SVector3 tmp = SVector3::Zero();
    if (length != 0.0f)
    {
        tmp.x = x / length;
        tmp.y = y / length;
        tmp.z = z / length;
    }
    return tmp;
}


void SVector3::Normalize()
{
    float length = Magnitude();
    if (length == 0.0f)
    {
        return;
    }
    x /= length;
    y /= length;
    z /= length;
}


float SVector3::Magnitude() const
{
    return sqrtf(x * x + y * y + z * z);
}


float SVector3::SqrMagnitude() const
{
    return x * x + y * y + z * z;
}


float SVector3::Dot(const SVector3& a_vector1, const SVector3& a_vector2)
{
    return ((a_vector1.x * a_vector2.x) + (a_vector1.y * a_vector2.y) + (a_vector1.z * a_vector2.z));
}


SVector3 SVector3::Normalized(const SVector3& a_vector1)
{
    float length = a_vector1.Magnitude();
    SVector3 tmp = SVector3::Zero();
    if (length != 0.0f)
    {
        tmp.x /= a_vector1.x / length;
        tmp.y /= a_vector1.y / length;
        tmp.z /= a_vector1.z / length;
    }
    return tmp;
}


void SVector3::Normalize(SVector3& a_vector1)
{
    float length = a_vector1.Magnitude();
    if (length == 0.0f)
    {
        return;
    }
    a_vector1.x /= length;
    a_vector1.y /= length;
    a_vector1.z /= length;
}


float SVector3::Distance(const SVector3& a_vector1, const SVector3& a_vector2)
{
    auto tmp = a_vector1 - a_vector2;
    return tmp.Magnitude();
}


SVector3 SVector3::Cross(const SVector3 & a_vector1, const SVector3 & a_vector2)
{
    SVector3 tmp = SVector3::Zero();
    tmp.x = a_vector1.y * a_vector2.z - a_vector2.y * a_vector1.z;
    tmp.y = a_vector1.z * a_vector2.x - a_vector2.z * a_vector1.x;
    tmp.z = a_vector1.x * a_vector2.y - a_vector2.x * a_vector1.y;
    return tmp;
}


SVector3 SVector3::Zero()
{
    return SVector3(0.0f, 0.0f, 0.0f);
}


SVector3 SVector3::One()
{
    return SVector3(1.0f, 1.0f, 1.0f);
}


SVector3 SVector3::Right()
{
    return SVector3(1.0f, 0.0f, 0.0f);
}


SVector3 SVector3::Left()
{
    return SVector3(-1.0f, 0.0f, 0.0f);
}


SVector3 SVector3::Up()
{
    return SVector3(0.0f, 1.0f, 0.0f);
}


SVector3 SVector3::Down()
{
    return SVector3(0.0f, -1.0f, 0.0f);
}


SVector3 SVector3::Forward()
{
    return SVector3(0.0f, 0.0f, 1.0f);
}


SVector3 SVector3::Backward()
{
    return SVector3(0.0f, 0.0f, -1.0f);
}