#include "SVector4.h"
#include <math.h>
#include <limits>


SVector4::SVector4()
    : x(0.0f)
    , y(0.0f)
    , z(0.0f)
    , w(0.0f)
{
}


SVector4::SVector4(const float a_x, const float a_y, const float a_z, const float a_w)
    : x(a_x)
    , y(a_y)
    , z(a_z)
    , w(a_w)
{
}


SVector4 SVector4::Normalized() const
{
    float length = Length();
    SVector4 tmp = SVector4::Zero();
    if (length != 0.0f)
    {
        tmp.x = x / length;
        tmp.y = y / length;
        tmp.z = z / length;
        tmp.w = w / length;
    }
    return tmp;
}


void SVector4::Normalize()
{
    float length = Length();
    if (length == 0.0f)
    {
        return;
    }
    x /= length;
    y /= length;
    z /= length;
    w /= length;
}


float SVector4::Length() const
{
    return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}


float SVector4::Dot(const SVector4& a_vector1, const SVector4& a_vector2)
{
    return ((a_vector1.x * a_vector2.x) + (a_vector1.y * a_vector2.y) + (a_vector1.z * a_vector2.z) + (a_vector1.w * a_vector2.w));
}


SVector4 SVector4::Normalized(const SVector4& a_vector1)
{
    float length = a_vector1.Length();
    SVector4 tmp = SVector4::Zero();
    if (length != 0.0f)
    {
        tmp.x /= a_vector1.x / length;
        tmp.y /= a_vector1.y / length;
        tmp.z /= a_vector1.z / length;
        tmp.w /= a_vector1.w / length;
    }
    return tmp;
}


void SVector4::Normalize(SVector4& a_vector1)
{
    float length = a_vector1.Length();
    if (length == 0.0f)
    {
        return;
    }
    a_vector1.x /= length;
    a_vector1.y /= length;
    a_vector1.z /= length;
    a_vector1.w /= length;
}


float SVector4::Distance(const SVector4& a_vector1, const SVector4& a_vector2)
{
    SVector4 tmp = a_vector1 - a_vector2;
    return tmp.Length();
}


SVector4 SVector4::Zero()
{
    return SVector4(0.0f, 0.0f, 0.0f, 0.0f);
}


SVector4 SVector4::One()
{
    return SVector4(1.0f, 1.0f, 1.0f, 1.0f);
}