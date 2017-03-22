#include "SMatrix4x4.h"

SMatrix4x4::SMatrix4x4() :
	m_m11(1), m_m21(0), m_m31(0), m_m41(0),
	m_m12(0), m_m22(1), m_m32(0), m_m42(0),
	m_m13(0), m_m23(0), m_m33(1), m_m43(0),
	m_m14(0), m_m24(0), m_m34(0), m_m44(1)
{
}

SMatrix4x4::SMatrix4x4(
	float a_m11, float a_m12, float a_m13, float a_m14,
	float a_m21, float a_m22, float a_m23, float a_m24,
	float a_m31, float a_m32, float a_m33, float a_m34,
	float a_m41, float a_m42, float a_m43, float a_m44) :
	m_m11(a_m11), m_m21(a_m12), m_m31(a_m13), m_m41(a_m14),
	m_m12(a_m21), m_m22(a_m22), m_m32(a_m23), m_m42(a_m24),
	m_m13(a_m31), m_m23(a_m32), m_m33(a_m33), m_m43(a_m34),
	m_m14(a_m41), m_m24(a_m42), m_m34(a_m43), m_m44(a_m44)
{
	//m_m11 = a_m11;
	//m_m12 = a_m12;
	//m_m13 = a_m13;
	//m_m14 = a_m14;
	//m_m21 = a_m21;
	//m_m22 = a_m22;
	//m_m23 = a_m23;
	//m_m24 = a_m24;
	//m_m31 = a_m31;
	//m_m32 = a_m32;
	//m_m33 = a_m33;
	//m_m34 = a_m34;
	//m_m41 = a_m41;
	//m_m42 = a_m42;
	//m_m43 = a_m43;
	//m_m44 = a_m44;
}

SMatrix4x4 SMatrix4x4::Identity()
{
	return SMatrix4x4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

SMatrix4x4 operator +(SMatrix4x4 a_m1, SMatrix4x4 a_m2)
{
	return SMatrix4x4(
		a_m1.m_m11 + a_m2.m_m11, a_m1.m_m12 + a_m2.m_m12, a_m1.m_m13 + a_m2.m_m13, a_m1.m_m14 + a_m2.m_m14,
		a_m1.m_m21 + a_m2.m_m21, a_m1.m_m22 + a_m2.m_m22, a_m1.m_m23 + a_m2.m_m23, a_m1.m_m24 + a_m2.m_m24,
		a_m1.m_m31 + a_m2.m_m31, a_m1.m_m32 + a_m2.m_m32, a_m1.m_m33 + a_m2.m_m33, a_m1.m_m34 + a_m2.m_m34,
		a_m1.m_m41 + a_m2.m_m41, a_m1.m_m42 + a_m2.m_m42, a_m1.m_m43 + a_m2.m_m43, a_m1.m_m44 + a_m2.m_m44);
}

SMatrix4x4 operator -(SMatrix4x4 a_m1, SMatrix4x4 a_m2)
{
	return SMatrix4x4(
		a_m1.m_m11 - a_m2.m_m11, a_m1.m_m12 - a_m2.m_m12, a_m1.m_m13 - a_m2.m_m13, a_m1.m_m14 - a_m2.m_m14,
		a_m1.m_m21 - a_m2.m_m21, a_m1.m_m22 - a_m2.m_m22, a_m1.m_m23 - a_m2.m_m23, a_m1.m_m24 - a_m2.m_m24,
		a_m1.m_m31 - a_m2.m_m31, a_m1.m_m32 - a_m2.m_m32, a_m1.m_m33 - a_m2.m_m33, a_m1.m_m34 - a_m2.m_m34,
		a_m1.m_m41 - a_m2.m_m41, a_m1.m_m42 - a_m2.m_m42, a_m1.m_m43 - a_m2.m_m43, a_m1.m_m44 - a_m2.m_m44);
}

SMatrix4x4 operator *(SMatrix4x4 a_m1, SMatrix4x4 a_m2)
{
	return SMatrix4x4(
		a_m1.m_m11 * a_m2.m_m11 + a_m1.m_m21 * a_m2.m_m12 + a_m1.m_m31 * a_m2.m_m13 + a_m1.m_m41 * a_m2.m_m14,
		a_m1.m_m12 * a_m2.m_m11 + a_m1.m_m22 * a_m2.m_m12 + a_m1.m_m32 * a_m2.m_m13 + a_m1.m_m42 * a_m2.m_m14,
		a_m1.m_m13 * a_m2.m_m11 + a_m1.m_m23 * a_m2.m_m12 + a_m1.m_m33 * a_m2.m_m13 + a_m1.m_m43 * a_m2.m_m14,
		a_m1.m_m14 * a_m2.m_m11 + a_m1.m_m24 * a_m2.m_m12 + a_m1.m_m34 * a_m2.m_m13 + a_m1.m_m44 * a_m2.m_m14,
		a_m1.m_m11 * a_m2.m_m21 + a_m1.m_m21 * a_m2.m_m22 + a_m1.m_m31 * a_m2.m_m23 + a_m1.m_m41 * a_m2.m_m24,
		a_m1.m_m12 * a_m2.m_m21 + a_m1.m_m22 * a_m2.m_m22 + a_m1.m_m32 * a_m2.m_m23 + a_m1.m_m42 * a_m2.m_m24,
		a_m1.m_m13 * a_m2.m_m21 + a_m1.m_m23 * a_m2.m_m22 + a_m1.m_m33 * a_m2.m_m23 + a_m1.m_m43 * a_m2.m_m24,
		a_m1.m_m14 * a_m2.m_m21 + a_m1.m_m24 * a_m2.m_m22 + a_m1.m_m34 * a_m2.m_m23 + a_m1.m_m44 * a_m2.m_m24,
		a_m1.m_m11 * a_m2.m_m31 + a_m1.m_m21 * a_m2.m_m32 + a_m1.m_m31 * a_m2.m_m33 + a_m1.m_m41 * a_m2.m_m34,
		a_m1.m_m12 * a_m2.m_m31 + a_m1.m_m22 * a_m2.m_m32 + a_m1.m_m32 * a_m2.m_m33 + a_m1.m_m42 * a_m2.m_m34,
		a_m1.m_m13 * a_m2.m_m31 + a_m1.m_m23 * a_m2.m_m32 + a_m1.m_m33 * a_m2.m_m33 + a_m1.m_m43 * a_m2.m_m34,
		a_m1.m_m14 * a_m2.m_m31 + a_m1.m_m24 * a_m2.m_m32 + a_m1.m_m34 * a_m2.m_m33 + a_m1.m_m44 * a_m2.m_m34,
		a_m1.m_m11 * a_m2.m_m41 + a_m1.m_m21 * a_m2.m_m42 + a_m1.m_m31 * a_m2.m_m43 + a_m1.m_m41 * a_m2.m_m44,
		a_m1.m_m12 * a_m2.m_m41 + a_m1.m_m22 * a_m2.m_m42 + a_m1.m_m32 * a_m2.m_m43 + a_m1.m_m42 * a_m2.m_m44,
		a_m1.m_m13 * a_m2.m_m41 + a_m1.m_m23 * a_m2.m_m42 + a_m1.m_m33 * a_m2.m_m43 + a_m1.m_m43 * a_m2.m_m44,
		a_m1.m_m14 * a_m2.m_m41 + a_m1.m_m24 * a_m2.m_m42 + a_m1.m_m34 * a_m2.m_m43 + a_m1.m_m44 * a_m2.m_m44);
}

SMatrix4x4 operator *(SMatrix4x4 a_m, float a_f)
{
	return SMatrix4x4(
		a_m.m_m11 * a_f, a_m.m_m12 * a_f, a_m.m_m13 * a_f, a_m.m_m14 * a_f,
		a_m.m_m21 * a_f, a_m.m_m22 * a_f, a_m.m_m23 * a_f, a_m.m_m24 * a_f,
		a_m.m_m31 * a_f, a_m.m_m32 * a_f, a_m.m_m33 * a_f, a_m.m_m34 * a_f,
		a_m.m_m41 * a_f, a_m.m_m42 * a_f, a_m.m_m43 * a_f, a_m.m_m44 * a_f);
}

SMatrix4x4 operator *(float a_f, SMatrix4x4 a_m)
{
	return a_m * a_f;
}

//SVector4 operator *(SMatrix4x4 a_m, SVector3 a_v)
//{
//	return SVector3(); // WIP
//}
//SVector4 operator *(SVector3 a_v, SMatrix4x4 a_m)
//{
//	return a_m * a_v; // ERROR
//}

bool operator ==(SMatrix4x4 a_m1, SMatrix4x4 a_m2)
{
	float epsilon = std::numeric_limits<float>::epsilon();
	return (
		(a_m1.m_m11 >= a_m2.m_m11 - epsilon && a_m1.m_m11 <= a_m2.m_m11 + epsilon) &&
		(a_m1.m_m12 >= a_m2.m_m12 - epsilon && a_m1.m_m12 <= a_m2.m_m12 + epsilon) &&
		(a_m1.m_m13 >= a_m2.m_m13 - epsilon && a_m1.m_m13 <= a_m2.m_m13 + epsilon) &&
		(a_m1.m_m14 >= a_m2.m_m14 - epsilon && a_m1.m_m14 <= a_m2.m_m14 + epsilon) &&
		(a_m1.m_m21 >= a_m2.m_m21 - epsilon && a_m1.m_m21 <= a_m2.m_m21 + epsilon) &&
		(a_m1.m_m22 >= a_m2.m_m22 - epsilon && a_m1.m_m22 <= a_m2.m_m22 + epsilon) &&
		(a_m1.m_m23 >= a_m2.m_m23 - epsilon && a_m1.m_m23 <= a_m2.m_m23 + epsilon) &&
		(a_m1.m_m24 >= a_m2.m_m24 - epsilon && a_m1.m_m24 <= a_m2.m_m24 + epsilon) &&
		(a_m1.m_m31 >= a_m2.m_m31 - epsilon && a_m1.m_m31 <= a_m2.m_m31 + epsilon) &&
		(a_m1.m_m32 >= a_m2.m_m32 - epsilon && a_m1.m_m32 <= a_m2.m_m32 + epsilon) &&
		(a_m1.m_m33 >= a_m2.m_m33 - epsilon && a_m1.m_m33 <= a_m2.m_m33 + epsilon) &&
		(a_m1.m_m34 >= a_m2.m_m34 - epsilon && a_m1.m_m34 <= a_m2.m_m34 + epsilon) &&
		(a_m1.m_m41 >= a_m2.m_m41 - epsilon && a_m1.m_m41 <= a_m2.m_m41 + epsilon) &&
		(a_m1.m_m42 >= a_m2.m_m42 - epsilon && a_m1.m_m42 <= a_m2.m_m42 + epsilon) &&
		(a_m1.m_m43 >= a_m2.m_m43 - epsilon && a_m1.m_m43 <= a_m2.m_m43 + epsilon) &&
		(a_m1.m_m44 >= a_m2.m_m44 - epsilon && a_m1.m_m44 <= a_m2.m_m44 + epsilon));
}

bool operator !=(SMatrix4x4 a_m1, SMatrix4x4 a_m2)
{
	return !(a_m1 == a_m2);
}

SMatrix4x4 SMatrix4x4::Transpose(SMatrix4x4 a_m)
{
	return SMatrix4x4(
		a_m.m_m11, a_m.m_m21, a_m.m_m31, a_m.m_m41,
		a_m.m_m12, a_m.m_m22, a_m.m_m32, a_m.m_m42,
		a_m.m_m13, a_m.m_m23, a_m.m_m33, a_m.m_m43,
		a_m.m_m14, a_m.m_m24, a_m.m_m34, a_m.m_m44);
}

SMatrix4x4 SMatrix4x4::Scale(SVector3 a_v)
{
	SMatrix4x4 tmp = Identity();

	tmp.m_m11 = a_v.x1;
	tmp.m_m22 = a_v.y1;
	tmp.m_m33 = a_v.m_z;

	return tmp;
}

SMatrix4x4 SMatrix4x4::Translation(SVector3 a_v)
{
	SMatrix4x4 tmp = Identity();

	tmp.m_m41 = a_v.x1;
	tmp.m_m42 = a_v.y1;
	tmp.m_m43 = a_v.m_z;

	return tmp;
}

SMatrix4x4 SMatrix4x4::RotationX(float a_f)
{
	SMatrix4x4 tmp = Identity();

	tmp.m_m22 = tmp.m_m33 = static_cast<float>(cos(a_f));
	tmp.m_m23 = static_cast<float>(sin(a_f));
	tmp.m_m32 = -tmp.m_m23;

	return tmp;
}

SMatrix4x4 SMatrix4x4::RotationY(float a_f)
{
	SMatrix4x4 tmp = Identity();

	tmp.m_m11 = tmp.m_m33 = static_cast<float>(cos(a_f));
	tmp.m_m31 = static_cast<float>(sin(a_f));
	tmp.m_m13 = -tmp.m_m31;

	return tmp;
}

SMatrix4x4 SMatrix4x4::RotationZ(float a_f)
{
	SMatrix4x4 tmp = Identity();

	tmp.m_m11 = tmp.m_m22 = static_cast<float>(cos(a_f));
	tmp.m_m12 = static_cast<float>(sin(a_f));
	tmp.m_m21 = -tmp.m_m12;

	return tmp;
}

SMatrix4x4 SMatrix4x4::Invert(SMatrix4x4 a_m)
{
	SMatrix4x4 tmp = Identity();

	float invDet = 1.0f / Determinant(a_m);

	tmp.m_m11 = invDet * (a_m.m_m23 * a_m.m_m34 * a_m.m_m42 - a_m.m_m24 * a_m.m_m33 * a_m.m_m42 + a_m.m_m24 * a_m.m_m32 * a_m.m_m43 - a_m.m_m22 * a_m.m_m34 * a_m.m_m43 - a_m.m_m23 * a_m.m_m32 * a_m.m_m44 + a_m.m_m22 * a_m.m_m33 * a_m.m_m44);
	tmp.m_m12 = invDet * (a_m.m_m14 * a_m.m_m33 * a_m.m_m42 - a_m.m_m13 * a_m.m_m34 * a_m.m_m42 - a_m.m_m14 * a_m.m_m32 * a_m.m_m43 + a_m.m_m12 * a_m.m_m34 * a_m.m_m43 + a_m.m_m13 * a_m.m_m32 * a_m.m_m44 - a_m.m_m12 * a_m.m_m33 * a_m.m_m44);
	tmp.m_m13 = invDet * (a_m.m_m13 * a_m.m_m24 * a_m.m_m42 - a_m.m_m14 * a_m.m_m23 * a_m.m_m42 + a_m.m_m14 * a_m.m_m22 * a_m.m_m43 - a_m.m_m12 * a_m.m_m24 * a_m.m_m43 - a_m.m_m13 * a_m.m_m22 * a_m.m_m44 + a_m.m_m12 * a_m.m_m23 * a_m.m_m44);
	tmp.m_m14 = invDet * (a_m.m_m14 * a_m.m_m23 * a_m.m_m32 - a_m.m_m13 * a_m.m_m24 * a_m.m_m32 - a_m.m_m14 * a_m.m_m22 * a_m.m_m33 + a_m.m_m12 * a_m.m_m24 * a_m.m_m33 + a_m.m_m13 * a_m.m_m22 * a_m.m_m34 - a_m.m_m12 * a_m.m_m23 * a_m.m_m34);
	tmp.m_m21 = invDet * (a_m.m_m24 * a_m.m_m33 * a_m.m_m41 - a_m.m_m23 * a_m.m_m34 * a_m.m_m41 - a_m.m_m24 * a_m.m_m31 * a_m.m_m43 + a_m.m_m21 * a_m.m_m34 * a_m.m_m43 + a_m.m_m23 * a_m.m_m31 * a_m.m_m44 - a_m.m_m21 * a_m.m_m33 * a_m.m_m44);
	tmp.m_m22 = invDet * (a_m.m_m13 * a_m.m_m34 * a_m.m_m41 - a_m.m_m14 * a_m.m_m33 * a_m.m_m41 + a_m.m_m14 * a_m.m_m31 * a_m.m_m43 - a_m.m_m11 * a_m.m_m34 * a_m.m_m43 - a_m.m_m13 * a_m.m_m31 * a_m.m_m44 + a_m.m_m11 * a_m.m_m33 * a_m.m_m44);
	tmp.m_m23 = invDet * (a_m.m_m14 * a_m.m_m23 * a_m.m_m41 - a_m.m_m13 * a_m.m_m24 * a_m.m_m41 - a_m.m_m14 * a_m.m_m21 * a_m.m_m43 + a_m.m_m11 * a_m.m_m24 * a_m.m_m43 + a_m.m_m13 * a_m.m_m21 * a_m.m_m44 - a_m.m_m11 * a_m.m_m23 * a_m.m_m44);
	tmp.m_m24 = invDet * (a_m.m_m13 * a_m.m_m24 * a_m.m_m31 - a_m.m_m14 * a_m.m_m23 * a_m.m_m31 + a_m.m_m14 * a_m.m_m21 * a_m.m_m33 - a_m.m_m11 * a_m.m_m24 * a_m.m_m33 - a_m.m_m13 * a_m.m_m21 * a_m.m_m34 + a_m.m_m11 * a_m.m_m23 * a_m.m_m34);
	tmp.m_m31 = invDet * (a_m.m_m22 * a_m.m_m34 * a_m.m_m41 - a_m.m_m24 * a_m.m_m32 * a_m.m_m41 + a_m.m_m24 * a_m.m_m31 * a_m.m_m42 - a_m.m_m21 * a_m.m_m34 * a_m.m_m42 - a_m.m_m22 * a_m.m_m31 * a_m.m_m44 + a_m.m_m21 * a_m.m_m32 * a_m.m_m44);
	tmp.m_m32 = invDet * (a_m.m_m14 * a_m.m_m32 * a_m.m_m41 - a_m.m_m12 * a_m.m_m34 * a_m.m_m41 - a_m.m_m14 * a_m.m_m31 * a_m.m_m42 + a_m.m_m11 * a_m.m_m34 * a_m.m_m42 + a_m.m_m12 * a_m.m_m31 * a_m.m_m44 - a_m.m_m11 * a_m.m_m32 * a_m.m_m44);
	tmp.m_m33 = invDet * (a_m.m_m12 * a_m.m_m24 * a_m.m_m41 - a_m.m_m14 * a_m.m_m22 * a_m.m_m41 + a_m.m_m14 * a_m.m_m21 * a_m.m_m42 - a_m.m_m11 * a_m.m_m24 * a_m.m_m42 - a_m.m_m12 * a_m.m_m21 * a_m.m_m44 + a_m.m_m11 * a_m.m_m22 * a_m.m_m44);
	tmp.m_m34 = invDet * (a_m.m_m14 * a_m.m_m22 * a_m.m_m31 - a_m.m_m12 * a_m.m_m24 * a_m.m_m31 - a_m.m_m14 * a_m.m_m21 * a_m.m_m32 + a_m.m_m11 * a_m.m_m24 * a_m.m_m32 + a_m.m_m12 * a_m.m_m21 * a_m.m_m34 - a_m.m_m11 * a_m.m_m22 * a_m.m_m34);
	tmp.m_m41 = invDet * (a_m.m_m23 * a_m.m_m32 * a_m.m_m41 - a_m.m_m22 * a_m.m_m33 * a_m.m_m41 - a_m.m_m23 * a_m.m_m31 * a_m.m_m42 + a_m.m_m21 * a_m.m_m33 * a_m.m_m42 + a_m.m_m22 * a_m.m_m31 * a_m.m_m43 - a_m.m_m21 * a_m.m_m32 * a_m.m_m43);
	tmp.m_m42 = invDet * (a_m.m_m12 * a_m.m_m33 * a_m.m_m41 - a_m.m_m13 * a_m.m_m32 * a_m.m_m41 + a_m.m_m13 * a_m.m_m31 * a_m.m_m42 - a_m.m_m11 * a_m.m_m33 * a_m.m_m42 - a_m.m_m12 * a_m.m_m31 * a_m.m_m43 + a_m.m_m11 * a_m.m_m32 * a_m.m_m43);
	tmp.m_m43 = invDet * (a_m.m_m13 * a_m.m_m22 * a_m.m_m41 - a_m.m_m12 * a_m.m_m23 * a_m.m_m41 - a_m.m_m13 * a_m.m_m21 * a_m.m_m42 + a_m.m_m11 * a_m.m_m23 * a_m.m_m42 + a_m.m_m12 * a_m.m_m21 * a_m.m_m43 - a_m.m_m11 * a_m.m_m22 * a_m.m_m43);
	tmp.m_m44 = invDet * (a_m.m_m12 * a_m.m_m23 * a_m.m_m31 - a_m.m_m13 * a_m.m_m22 * a_m.m_m31 + a_m.m_m13 * a_m.m_m21 * a_m.m_m32 - a_m.m_m11 * a_m.m_m23 * a_m.m_m32 - a_m.m_m12 * a_m.m_m21 * a_m.m_m33 + a_m.m_m11 * a_m.m_m22 * a_m.m_m33);

	return tmp;
}

float SMatrix4x4::Determinant(SMatrix4x4 a_m)
{
	float a = a_m.m_m11 * (
		(a_m.m_m22 * a_m.m_m33 * a_m.m_m44) + (a_m.m_m23 * a_m.m_m34 * a_m.m_m42) + (a_m.m_m24 * a_m.m_m32 * a_m.m_m43) -
		(a_m.m_m24 * a_m.m_m33 * a_m.m_m42) - (a_m.m_m23 * a_m.m_m32 * a_m.m_m44) - (a_m.m_m22 * a_m.m_m34 * a_m.m_m43));

	float b = a_m.m_m21 * (
		(a_m.m_m12 * a_m.m_m33 * a_m.m_m44) + (a_m.m_m32 * a_m.m_m34 * a_m.m_m42) + (a_m.m_m14 * a_m.m_m32 * a_m.m_m43) -
		(a_m.m_m14 * a_m.m_m33 * a_m.m_m42) - (a_m.m_m13 * a_m.m_m32 * a_m.m_m44) - (a_m.m_m12 * a_m.m_m34 * a_m.m_m43));

	float c = a_m.m_m31 * (
		(a_m.m_m12 * a_m.m_m23 * a_m.m_m44) + (a_m.m_m13 * a_m.m_m24 * a_m.m_m42) + (a_m.m_m14 * a_m.m_m22 * a_m.m_m43) -
		(a_m.m_m14 * a_m.m_m23 * a_m.m_m42) - (a_m.m_m13 * a_m.m_m22 * a_m.m_m44) - (a_m.m_m12 * a_m.m_m24 * a_m.m_m43));

	float d = a_m.m_m41 * (
		(a_m.m_m12 * a_m.m_m23 * a_m.m_m34) + (a_m.m_m13 * a_m.m_m24 * a_m.m_m32) + (a_m.m_m14 * a_m.m_m22 * a_m.m_m33) -
		(a_m.m_m14 * a_m.m_m23 * a_m.m_m32) - (a_m.m_m13 * a_m.m_m22 * a_m.m_m34) - (a_m.m_m12 * a_m.m_m24 * a_m.m_m33));

	return a - b + c - d;
}
