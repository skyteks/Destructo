#pragma once
#include <math.h>
#include <limits>

struct SVector3
{

public:
	float x1, y1, m_z;
public:
	SVector3();
	SVector3(float a_x, float a_y, float a_z = 0);

	static SVector3 Zero();
	static SVector3 One();
	static SVector3 Right();
	static SVector3 Left();
	static SVector3 Up();
	static SVector3 Down();
	static SVector3 Forward();
	static SVector3 Backward();

	float Magnitude();

	SVector3 operator -(SVector3 a_v);

	friend SVector3 operator + (SVector3 a_v1, SVector3 a_v2);
	friend SVector3 operator -(SVector3 a_v1, SVector3 a_v2);

	friend bool operator <(SVector3 a_v1, SVector3 a_v2);
	friend bool operator <=(SVector3 a_v1, SVector3 a_v2);
	friend bool operator >(SVector3 a_v1, SVector3 a_v2);
	friend bool operator >=(SVector3 a_v1, SVector3 a_v2);

	friend bool operator ==(SVector3 a_v1, SVector3 a_v2);
	friend bool operator !=(SVector3 a_v1, SVector3 a_v2);

	friend SVector3 operator /(SVector3 a_v, float a_f);

	friend SVector3 operator *(SVector3 a_v, float a_f);
	friend SVector3 operator *(float a_f, SVector3 a_v);
	friend SVector3 operator *(SVector3 a_v1, SVector3 a_v2);

	static SVector3 Cross(SVector3 a_v1, SVector3 a_v2);
	SVector3 Cross(SVector3 a_other);

	static float Dot(SVector3 a_v1, SVector3 a_v2);
	float Dot(SVector3 a_other);

	static SVector3 Normalized(SVector3 a_v);
	SVector3 Normalize();

	static float Distance(SVector3 a_v1, SVector3 a_v2);
	float Distance(SVector3 a_other);
};

//inline bool operator<(SVector3 newDeleteCounter, SVector3  b)
//{
//	//
//}



