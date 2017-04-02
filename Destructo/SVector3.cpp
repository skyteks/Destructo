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

float SVector3::Length() const
{
	return static_cast<float>(sqrt(x * x + y * y + z * z));
}

float SVector3::Dot(const SVector3& a_vector1, const SVector3& a_vector2)
{
	return ((a_vector1.x * a_vector2.x) + (a_vector1.y * a_vector2.y) + (a_vector1.z * a_vector2.z));
}
void SVector3::Normalize(SVector3& a_vector1)
{
	float length = a_vector1.Length();

	a_vector1.x /= length;
	a_vector1.y /= length;
	a_vector1.z /= length;
}
SVector3 SVector3::Normalized(const SVector3& a_vector1)
{
	SVector3 tmp;
	float length = a_vector1.Length();

	tmp.x = a_vector1.x / length;
	tmp.y /= a_vector1.y / length;
	tmp.z /= a_vector1.z / length;

	return tmp;
}
float SVector3::Distance(const SVector3& a_vector1, const SVector3& a_vector2)
{
	auto tmp = a_vector1 - a_vector2;
	return tmp.Length();
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