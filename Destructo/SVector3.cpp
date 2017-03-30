#include "SVector3.h"

SVector3::SVector3()
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
{
}

SVector3::SVector3(float a_x, float a_y, float a_z) 
	: x(a_x)
	, y(a_y)
	, z(a_z)
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
	return SVector3(1, 0, 0);
}

SVector3 SVector3::Left()
{
	return SVector3(-1, 0, 0);
}

SVector3 SVector3::Up()
{
	return SVector3(0, 1, 0);
}

SVector3 SVector3::Down()
{
	return SVector3(0, -1, 0);
}

SVector3 SVector3::Forward()
{
	return SVector3(0, 0, 1);
}

SVector3 SVector3::Backward()
{
	return SVector3(0, 0, -1);
}

float SVector3::Magnitude()
{
	return static_cast<float>(sqrt(x * x + y * y + z * z));
}

SVector3 SVector3::operator -(SVector3 a_v)
{
	return SVector3(-a_v.x, -a_v.y, -a_v.z);
}

SVector3 operator +(SVector3 a_v1, SVector3 a_v2)
{
	return SVector3(a_v1.x + a_v2.x, a_v1.y + a_v2.y, a_v1.z + a_v2.z);
}
SVector3 operator -(SVector3 a_v1, SVector3 a_v2)
{
	return SVector3(a_v1.x - a_v2.x, a_v1.y - a_v2.y, a_v1.z - a_v2.z);
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
	float epsilon = std::numeric_limits<float>::epsilon();
	return (a_v1.x >= a_v2.x - epsilon && a_v1.x <= a_v2.x + epsilon) &&
		(a_v1.y >= a_v2.y - epsilon && a_v1.y <= a_v2.y + epsilon) &&
		(a_v1.z >= a_v2.z - epsilon && a_v1.z <= a_v2.z + epsilon);
}
bool operator !=(SVector3 a_v1, SVector3 a_v2)
{
	return !(a_v1 == a_v2);
}

SVector3 operator /(SVector3 a_v, float a_f)
{
	return SVector3(a_v.x / a_f, a_v.y / a_f, a_v.z / a_f);
}

SVector3 operator *(SVector3 a_v, float a_f)
{
	return SVector3(a_v.x * a_f, a_v.y * a_f, a_v.z * a_f);
}
SVector3 operator *(float a_f, SVector3 a_v)
{
	return a_v * a_f;
}
SVector3 operator *(SVector3 a_v1, SVector3 a_v2)
{
	return SVector3(a_v1.x * a_v2.x, a_v1.y * a_v2.y, a_v1.z * a_v2.z);
}


SVector3 SVector3::Cross(SVector3 a_v1, SVector3 a_v2)
{
	return SVector3(a_v1.y * a_v2.z - a_v1.z * a_v2.y,
		a_v1.z * a_v2.x - a_v1.x * a_v2.z,
		a_v1.z * a_v2.y - a_v1.y * a_v2.x);
}
SVector3 SVector3::Cross(SVector3 a_other)
{
	return Cross(*this, a_other);
}

float SVector3::Dot(SVector3 a_v1, SVector3 a_v2)
{
	return a_v1.x * a_v2.x +
		a_v1.y * a_v2.y +
		a_v1.z * a_v2.z;
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

	return SVector3(a_v.x * inverse,
		a_v.y * inverse,
		a_v.z * inverse);
}
SVector3 SVector3::Normalize()
{
	return Normalized(*this);
}

float SVector3::Distance(SVector3 a_v1, SVector3 a_v2)
{
	return static_cast<float>(sqrt(
		(a_v1.x - a_v2.x) * (a_v1.x - a_v2.x) +
		(a_v1.y - a_v2.y) * (a_v1.y - a_v2.y) +
		(a_v1.z - a_v2.z) * (a_v1.z - a_v2.z)
	));
}
float SVector3::Distance(SVector3 a_other)
{
	return Distance(*this, a_other);
}
