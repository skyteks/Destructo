#include "SVector4.h"


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
    SVector4 tmp;
    float length = this->Length();

    tmp.x = this->x / length;
    tmp.y = this->y / length;
    tmp.z = this->z / length;
    tmp.w = this->w / length;

    return tmp;
}
void SVector4::Normalize()
{
    float length = this->Length();

    this->x /= length;
    this->y /= length;
    this->z /= length;
    this->w /= length;
}
float SVector4::Length() const
{
    return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

float SVector4::Dot(const SVector4& a_vector1, const SVector4& a_vector2)
{
    return ((a_vector1.x * a_vector2.x) + (a_vector1.y * a_vector2.y) + (a_vector1.z * a_vector2.z) + (a_vector1.w * a_vector2.w));
}

void SVector4::Normalize(SVector4& a_vector1)
{
    float length = a_vector1.Length();

    a_vector1.x /= length;
    a_vector1.y /= length;
    a_vector1.z /= length;
    a_vector1.w /= length;
}
SVector4 SVector4::Normalized(const SVector4& a_vector1)
{
    SVector4 tmp;
    float length = a_vector1.Length();

    tmp.x = a_vector1.x / length;
    tmp.y /= a_vector1.y / length;
    tmp.z /= a_vector1.z / length;
    tmp.w /= a_vector1.w / length;

    return tmp;
}
float SVector4::Distance(const SVector4& a_vector1, const SVector4& a_vector2)
{
    auto tmp = a_vector1 - a_vector2;
    return tmp.Length();
}

SVector4 SVector4::Zero()
{
    return SVector4(0, 0, 0, 0);
}

SVector4 SVector4::One()
{
    return SVector4(1, 1, 1, 1);
}