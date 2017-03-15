#pragma once
#include <limits>
#include "SVector3.h"


struct SMatrix4x4
{
public:
	float m_m11, m_m12, m_m13, m_m14;
	float m_m21, m_m22, m_m23, m_m24;
	float m_m31, m_m32, m_m33, m_m34;
	float m_m41, m_m42, m_m43, m_m44;


public:
	SMatrix4x4();
	SMatrix4x4(float a_m11, float a_m12, float a_m13, float a_m14,
		float a_m21, float a_m22, float a_m23, float a_m24,
		float a_m31, float a_m32, float a_m33, float a_m34,
		float a_m41, float a_m42, float a_m43, float a_m44);

	static SMatrix4x4 Identity();

	friend SMatrix4x4 operator +(SMatrix4x4 a_m1, SMatrix4x4 a_m2);
	friend SMatrix4x4 operator -(SMatrix4x4 a_m1, SMatrix4x4 a_m2);

	friend SMatrix4x4 operator *(SMatrix4x4 a_m1, SMatrix4x4 a_m2);
	friend SMatrix4x4 operator *(SMatrix4x4 a_m, float a_f);
	friend SMatrix4x4 operator *(float a_f, SMatrix4x4 a_m);
	//friend SVector4 operator *(SMatrix4x4 a_m, SVector3 a_v);
	//friend SVector4 operator *(SVector3 a_v, SMatrix4x4 a_m);

	friend bool operator ==(SMatrix4x4 a_m1, SMatrix4x4 a_m2);
	friend bool operator !=(SMatrix4x4 a_m1, SMatrix4x4 a_m2);

	static SMatrix4x4 Transpose(SMatrix4x4 a_m);

	static SMatrix4x4 Scale(SVector3 a_v);
	static SMatrix4x4 Translation(SVector3 a_v);
	static SMatrix4x4 RotationX(float a_f);
	static SMatrix4x4 RotationY(float a_f);
	static SMatrix4x4 RotationZ(float a_f);

	static SMatrix4x4 Invert(SMatrix4x4 a_m);

	static float Determinant(SMatrix4x4 a_m);
};

