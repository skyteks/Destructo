#include "SVector3.h"

SVector3::SVector3() : x1(0), y1(0), m_z(0)
{
}

SVector3::SVector3(float a_x, float a_y, float a_z) : x1(a_x), y1(a_y), m_z(a_z)
{
}

SVector3 SVector3::Zero()
{
	return SVector3(0, 0, 0);
}

SVector3 SVector3::One()
{
	return SVector3(1, 1, 1);
}

SVector3 SVector3::Right()
{
	return SVector3(1,0,0);
}

SVector3 SVector3::Left()
{
	return SVector3(-1, 0, 0);
}

SVector3 SVector3::Up()
{
	return SVector3(0,1,0);
}

SVector3 SVector3::Down()
{
	return SVector3(0,-1,0);
}

SVector3 SVector3::Forward()
{
	return SVector3(0,0,1);
}

SVector3 SVector3::Backward()
{
	return SVector3(0, 0, -1);
}

float SVector3::Magnitude()
{
	return static_cast<float>(sqrt(x1 * x1 + y1 * y1 + m_z * m_z));
}

SVector3 SVector3::operator -(SVector3 a_v)
{
	return SVector3(-a_v.x1, -a_v.y1, -a_v.m_z);
}

SVector3 operator +(SVector3 a_v1, SVector3 a_v2)
{
	return SVector3(a_v1.x1 + a_v2.x1, a_v1.y1 + a_v2.y1, a_v1.m_z + a_v2.m_z);
}
SVector3 operator -(SVector3 a_v1, SVector3 a_v2)
{
	return SVector3(a_v1.x1 - a_v2.x1, a_v1.y1 - a_v2.y1, a_v1.m_z - a_v2.m_z);
}

bool operator <(SVector3 a_v1, SVector3 a_v2)
{
	return a_v1.Magnitude() < a_v2.Magnitude();
}
bool operator <=(SVector3 a_v1, SVector3 a_v2)
{
	return a_v1.Magnitude() <= a_v2.Magnitude();
}
bool operator >(SVector3 a_v1, SVector3 a_v2)
{
	return a_v1.Magnitude() > a_v2.Magnitude();
}
bool operator >=(SVector3 a_v1, SVector3 a_v2)
{
	return a_v1.Magnitude() >= a_v2.Magnitude();
}

bool operator ==(SVector3 a_v1, SVector3 a_v2)
{
	return (a_v1.x1 >= a_v2.x1 - std::numeric_limits<float>::epsilon() && a_v1.x1 <= a_v2.x1 + std::numeric_limits<float>::epsilon()) &&
		(a_v1.y1 >= a_v2.y1 - std::numeric_limits<float>::epsilon() && a_v1.y1 <= a_v2.y1 + std::numeric_limits<float>::epsilon()) &&
		(a_v1.m_z >= a_v2.m_z - std::numeric_limits<float>::epsilon() && a_v1.m_z <= a_v2.m_z + std::numeric_limits<float>::epsilon());
}
bool operator !=(SVector3 a_v1, SVector3 a_v2)
{
	return !(a_v1 == a_v2);
}

SVector3 operator /(SVector3 a_v, float a_f)
{
	return SVector3(a_v.x1 / a_f, a_v.y1 / a_f, a_v.m_z / a_f);
}

SVector3 operator *(SVector3 a_v, float a_f)
{
	return SVector3(a_v.x1 * a_f, a_v.y1 * a_f, a_v.m_z * a_f);
}
SVector3 operator *(float a_f, SVector3 a_v)
{
	return a_v * a_f;
}
SVector3 operator *(SVector3 a_v1, SVector3 a_v2)
{
	return SVector3(a_v1.x1 * a_v2.x1, a_v1.y1 * a_v2.y1, a_v1.m_z * a_v2.m_z);
}


SVector3 SVector3::Cross(SVector3 a_v1, SVector3 a_v2)
{
	return SVector3(a_v1.y1 * a_v2.m_z - a_v1.m_z * a_v2.y1,
		a_v1.m_z * a_v2.x1 - a_v1.x1 * a_v2.m_z,
		a_v1.m_z * a_v2.y1 - a_v1.y1 * a_v2.x1);
}
SVector3 SVector3::Cross(SVector3 a_other)
{
	return Cross(*this, a_other);
}

float SVector3::Dot(SVector3 a_v1, SVector3 a_v2)
{
	return a_v1.x1 * a_v2.x1 +
		a_v1.y1 * a_v2.y1 +
		a_v1.m_z * a_v2.m_z;
}
float SVector3::Dot(SVector3 a_other)
{
	return Dot(*this, a_other);
}

SVector3 SVector3::Normalized(SVector3 a_v)
{
	if (a_v.Magnitude() <= std::numeric_limits<float>::epsilon())
	{
		return Zero();
	}

	float inverse = 1 / a_v.Magnitude();

	return SVector3(a_v.x1 * inverse,
		a_v.y1 * inverse,
		a_v.m_z * inverse);
}
SVector3 SVector3::Normalize()
{
	return Normalized(*this);
}

float SVector3::Distance(SVector3 a_v1, SVector3 a_v2)
{
	return static_cast<float>(sqrt(
		(a_v1.x1 - a_v2.x1) * (a_v1.x1 - a_v2.x1) +
		(a_v1.y1 - a_v2.y1) * (a_v1.y1 - a_v2.y1) +
		(a_v1.m_z - a_v2.m_z) * (a_v1.m_z - a_v2.m_z)
	));
}
float SVector3::Distance(SVector3 a_other)
{
	return Distance(*this, a_other);
}
