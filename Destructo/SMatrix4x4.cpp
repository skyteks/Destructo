#include "SMatrix4x4.h"

SMatrix4x4::SMatrix4x4() :
	m11(1.0f), m21(0.0f), m31(0.0f), m41(0.0f),
	m12(0.0f), m22(1.0f), m32(0.0f), m42(0.0f),
	m13(0.0f), m23(0.0f), m33(1.0f), m43(0.0f),
	m14(0.0f), m24(0.0f), m34(0.0f), m44(1.0f)
{
}

SMatrix4x4::SMatrix4x4(
	float a_m11, float a_m12, float a_m13, float a_m14,
	float a_m21, float a_m22, float a_m23, float a_m24,
	float a_m31, float a_m32, float a_m33, float a_m34,
	float a_m41, float a_m42, float a_m43, float a_m44) :
	m11(a_m11), m21(a_m12), m31(a_m13), m41(a_m14),
	m12(a_m21), m22(a_m22), m32(a_m23), m42(a_m24),
	m13(a_m31), m23(a_m32), m33(a_m33), m43(a_m34),
	m14(a_m41), m24(a_m42), m34(a_m43), m44(a_m44)
{
	//m11 = a_m11;
	//m12 = a_m12;
	//m13 = a_m13;
	//m14 = a_m14;
	//m21 = a_m21;
	//m22 = a_m22;
	//m23 = a_m23;
	//m24 = a_m24;
	//m31 = a_m31;
	//m32 = a_m32;
	//m33 = a_m33;
	//m34 = a_m34;
	//m41 = a_m41;
	//m42 = a_m42;
	//m43 = a_m43;
	//m44 = a_m44;
}

SMatrix4x4 SMatrix4x4::Identity()
{
	return SMatrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

SMatrix4x4 operator +(SMatrix4x4 a_matrix1, SMatrix4x4 a_matrix2)
{
	return SMatrix4x4(
		a_matrix1.m11 + a_matrix2.m11, a_matrix1.m12 + a_matrix2.m12, a_matrix1.m13 + a_matrix2.m13, a_matrix1.m14 + a_matrix2.m14,
		a_matrix1.m21 + a_matrix2.m21, a_matrix1.m22 + a_matrix2.m22, a_matrix1.m23 + a_matrix2.m23, a_matrix1.m24 + a_matrix2.m24,
		a_matrix1.m31 + a_matrix2.m31, a_matrix1.m32 + a_matrix2.m32, a_matrix1.m33 + a_matrix2.m33, a_matrix1.m34 + a_matrix2.m34,
		a_matrix1.m41 + a_matrix2.m41, a_matrix1.m42 + a_matrix2.m42, a_matrix1.m43 + a_matrix2.m43, a_matrix1.m44 + a_matrix2.m44);
}

SMatrix4x4 operator -(SMatrix4x4 a_matrix1, SMatrix4x4 a_matrix2)
{
	return SMatrix4x4(
		a_matrix1.m11 - a_matrix2.m11, a_matrix1.m12 - a_matrix2.m12, a_matrix1.m13 - a_matrix2.m13, a_matrix1.m14 - a_matrix2.m14,
		a_matrix1.m21 - a_matrix2.m21, a_matrix1.m22 - a_matrix2.m22, a_matrix1.m23 - a_matrix2.m23, a_matrix1.m24 - a_matrix2.m24,
		a_matrix1.m31 - a_matrix2.m31, a_matrix1.m32 - a_matrix2.m32, a_matrix1.m33 - a_matrix2.m33, a_matrix1.m34 - a_matrix2.m34,
		a_matrix1.m41 - a_matrix2.m41, a_matrix1.m42 - a_matrix2.m42, a_matrix1.m43 - a_matrix2.m43, a_matrix1.m44 - a_matrix2.m44);
}

SMatrix4x4 operator *(SMatrix4x4 a_matrix1, SMatrix4x4 a_matrix2)
{
	return SMatrix4x4(
		a_matrix1.m11 * a_matrix2.m11 + a_matrix1.m21 * a_matrix2.m12 + a_matrix1.m31 * a_matrix2.m13 + a_matrix1.m41 * a_matrix2.m14,
		a_matrix1.m12 * a_matrix2.m11 + a_matrix1.m22 * a_matrix2.m12 + a_matrix1.m32 * a_matrix2.m13 + a_matrix1.m42 * a_matrix2.m14,
		a_matrix1.m13 * a_matrix2.m11 + a_matrix1.m23 * a_matrix2.m12 + a_matrix1.m33 * a_matrix2.m13 + a_matrix1.m43 * a_matrix2.m14,
		a_matrix1.m14 * a_matrix2.m11 + a_matrix1.m24 * a_matrix2.m12 + a_matrix1.m34 * a_matrix2.m13 + a_matrix1.m44 * a_matrix2.m14,
		a_matrix1.m11 * a_matrix2.m21 + a_matrix1.m21 * a_matrix2.m22 + a_matrix1.m31 * a_matrix2.m23 + a_matrix1.m41 * a_matrix2.m24,
		a_matrix1.m12 * a_matrix2.m21 + a_matrix1.m22 * a_matrix2.m22 + a_matrix1.m32 * a_matrix2.m23 + a_matrix1.m42 * a_matrix2.m24,
		a_matrix1.m13 * a_matrix2.m21 + a_matrix1.m23 * a_matrix2.m22 + a_matrix1.m33 * a_matrix2.m23 + a_matrix1.m43 * a_matrix2.m24,
		a_matrix1.m14 * a_matrix2.m21 + a_matrix1.m24 * a_matrix2.m22 + a_matrix1.m34 * a_matrix2.m23 + a_matrix1.m44 * a_matrix2.m24,
		a_matrix1.m11 * a_matrix2.m31 + a_matrix1.m21 * a_matrix2.m32 + a_matrix1.m31 * a_matrix2.m33 + a_matrix1.m41 * a_matrix2.m34,
		a_matrix1.m12 * a_matrix2.m31 + a_matrix1.m22 * a_matrix2.m32 + a_matrix1.m32 * a_matrix2.m33 + a_matrix1.m42 * a_matrix2.m34,
		a_matrix1.m13 * a_matrix2.m31 + a_matrix1.m23 * a_matrix2.m32 + a_matrix1.m33 * a_matrix2.m33 + a_matrix1.m43 * a_matrix2.m34,
		a_matrix1.m14 * a_matrix2.m31 + a_matrix1.m24 * a_matrix2.m32 + a_matrix1.m34 * a_matrix2.m33 + a_matrix1.m44 * a_matrix2.m34,
		a_matrix1.m11 * a_matrix2.m41 + a_matrix1.m21 * a_matrix2.m42 + a_matrix1.m31 * a_matrix2.m43 + a_matrix1.m41 * a_matrix2.m44,
		a_matrix1.m12 * a_matrix2.m41 + a_matrix1.m22 * a_matrix2.m42 + a_matrix1.m32 * a_matrix2.m43 + a_matrix1.m42 * a_matrix2.m44,
		a_matrix1.m13 * a_matrix2.m41 + a_matrix1.m23 * a_matrix2.m42 + a_matrix1.m33 * a_matrix2.m43 + a_matrix1.m43 * a_matrix2.m44,
		a_matrix1.m14 * a_matrix2.m41 + a_matrix1.m24 * a_matrix2.m42 + a_matrix1.m34 * a_matrix2.m43 + a_matrix1.m44 * a_matrix2.m44);
}

SMatrix4x4 operator *(SMatrix4x4 a_matrix, float a_f)
{
	return SMatrix4x4(
		a_matrix.m11 * a_f, a_matrix.m12 * a_f, a_matrix.m13 * a_f, a_matrix.m14 * a_f,
		a_matrix.m21 * a_f, a_matrix.m22 * a_f, a_matrix.m23 * a_f, a_matrix.m24 * a_f,
		a_matrix.m31 * a_f, a_matrix.m32 * a_f, a_matrix.m33 * a_f, a_matrix.m34 * a_f,
		a_matrix.m41 * a_f, a_matrix.m42 * a_f, a_matrix.m43 * a_f, a_matrix.m44 * a_f);
}

SMatrix4x4 operator *(float a_f, SMatrix4x4 a_matrix)
{
	return a_matrix * a_f;
}

SVector4 operator *(SMatrix4x4 a_matrix, SVector3 a_vectorector)
{
	SVector4 result;

	/*
	    return CVector3(
        (lhs.x * rhs.mtx[1][1]) + (lhs.y * rhs.mtx[1][0]) + (lhs.z * rhs.mtx[2][0]),
        (lhs.x * rhs.mtx[1][2]) + (lhs.y * rhs.mtx[1][1]) + (lhs.z * rhs.mtx[2][1]),
        (lhs.x * rhs.mtx[1][3]) + (lhs.y * rhs.mtx[1][2]) + (lhs.z * rhs.mtx[2][2]));
	*/

	result.x = a_matrix.m11 * a_vectorector.x + a_matrix.m12 * a_vectorector.y + a_matrix.m13 * a_vectorector.z + a_matrix.m14 * 1.0f;
	result.y = a_matrix.m21 * a_vectorector.x + a_matrix.m22 * a_vectorector.y + a_matrix.m23 * a_vectorector.z + a_matrix.m24 * 1.0f;
	result.z = a_matrix.m31 * a_vectorector.x + a_matrix.m32 * a_vectorector.y + a_matrix.m33 * a_vectorector.z + a_matrix.m34 * 1.0f;
	result.w = a_matrix.m41 * a_vectorector.x + a_matrix.m42 * a_vectorector.y + a_matrix.m43 * a_vectorector.z + a_matrix.m44 * 1.0f;

	return result;
}
SVector4 operator *(SVector3 a_vector, SMatrix4x4 a_matrix)
{
	return a_matrix * a_vector;
}

bool operator ==(SMatrix4x4 a_matrix1, SMatrix4x4 a_matrix2)
{
	float epsilon = std::numeric_limits<float>::epsilon();
	return (
		(a_matrix1.m11 >= a_matrix2.m11 - epsilon && a_matrix1.m11 <= a_matrix2.m11 + epsilon) &&
		(a_matrix1.m12 >= a_matrix2.m12 - epsilon && a_matrix1.m12 <= a_matrix2.m12 + epsilon) &&
		(a_matrix1.m13 >= a_matrix2.m13 - epsilon && a_matrix1.m13 <= a_matrix2.m13 + epsilon) &&
		(a_matrix1.m14 >= a_matrix2.m14 - epsilon && a_matrix1.m14 <= a_matrix2.m14 + epsilon) &&
		(a_matrix1.m21 >= a_matrix2.m21 - epsilon && a_matrix1.m21 <= a_matrix2.m21 + epsilon) &&
		(a_matrix1.m22 >= a_matrix2.m22 - epsilon && a_matrix1.m22 <= a_matrix2.m22 + epsilon) &&
		(a_matrix1.m23 >= a_matrix2.m23 - epsilon && a_matrix1.m23 <= a_matrix2.m23 + epsilon) &&
		(a_matrix1.m24 >= a_matrix2.m24 - epsilon && a_matrix1.m24 <= a_matrix2.m24 + epsilon) &&
		(a_matrix1.m31 >= a_matrix2.m31 - epsilon && a_matrix1.m31 <= a_matrix2.m31 + epsilon) &&
		(a_matrix1.m32 >= a_matrix2.m32 - epsilon && a_matrix1.m32 <= a_matrix2.m32 + epsilon) &&
		(a_matrix1.m33 >= a_matrix2.m33 - epsilon && a_matrix1.m33 <= a_matrix2.m33 + epsilon) &&
		(a_matrix1.m34 >= a_matrix2.m34 - epsilon && a_matrix1.m34 <= a_matrix2.m34 + epsilon) &&
		(a_matrix1.m41 >= a_matrix2.m41 - epsilon && a_matrix1.m41 <= a_matrix2.m41 + epsilon) &&
		(a_matrix1.m42 >= a_matrix2.m42 - epsilon && a_matrix1.m42 <= a_matrix2.m42 + epsilon) &&
		(a_matrix1.m43 >= a_matrix2.m43 - epsilon && a_matrix1.m43 <= a_matrix2.m43 + epsilon) &&
		(a_matrix1.m44 >= a_matrix2.m44 - epsilon && a_matrix1.m44 <= a_matrix2.m44 + epsilon));
}

bool operator !=(SMatrix4x4 a_matrix1, SMatrix4x4 a_matrix2)
{
	return !(a_matrix1 == a_matrix2);
}

SMatrix4x4 SMatrix4x4::Transpose(SMatrix4x4 a_matrix)
{
	return SMatrix4x4(
		a_matrix.m11, a_matrix.m21, a_matrix.m31, a_matrix.m41,
		a_matrix.m12, a_matrix.m22, a_matrix.m32, a_matrix.m42,
		a_matrix.m13, a_matrix.m23, a_matrix.m33, a_matrix.m43,
		a_matrix.m14, a_matrix.m24, a_matrix.m34, a_matrix.m44);
}

SMatrix4x4 SMatrix4x4::Scale(SVector3 a_vector)
{
	SMatrix4x4 tmp = Identity();

	tmp.m11 = a_vector.x;
	tmp.m22 = a_vector.y;
	tmp.m33 = a_vector.z;

	return tmp;
}

SMatrix4x4 SMatrix4x4::Translation(SVector3 a_vector)
{
	SMatrix4x4 tmp = Identity();

	tmp.m41 = a_vector.x;
	tmp.m42 = a_vector.y;
	tmp.m43 = a_vector.z;

	return tmp;
}

SMatrix4x4 SMatrix4x4::RotationX(float a_f)
{
	SMatrix4x4 tmp = Identity();

	tmp.m22 = tmp.m33 = static_cast<float>(cos(a_f));
	tmp.m23 = static_cast<float>(sin(a_f));
	tmp.m32 = -tmp.m23;

	return tmp;
}

SMatrix4x4 SMatrix4x4::RotationY(float a_f)
{
	SMatrix4x4 tmp = Identity();

	tmp.m11 = tmp.m33 = static_cast<float>(cos(a_f));
	tmp.m31 = static_cast<float>(sin(a_f));
	tmp.m13 = -tmp.m31;

	return tmp;
}

SMatrix4x4 SMatrix4x4::RotationZ(float a_f)
{
	SMatrix4x4 tmp = Identity();

	tmp.m11 = tmp.m22 = cos(a_f);
	tmp.m12 = -sin(a_f);
	tmp.m21 = -tmp.m12;

	return tmp;

	/*
	return SMatrix4x4(
		cos(a_f), sin(a_f), 0, 0,
		-sin(a_f), cos(a_f), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	*/
}

SMatrix4x4 SMatrix4x4::Invert(SMatrix4x4 a_matrix)
{
	SMatrix4x4 tmp = Identity();

	float invDet = 1.0f / Determinant(a_matrix);

	tmp.m11 = invDet * (a_matrix.m23 * a_matrix.m34 * a_matrix.m42 - a_matrix.m24 * a_matrix.m33 * a_matrix.m42 + a_matrix.m24 * a_matrix.m32 * a_matrix.m43 - a_matrix.m22 * a_matrix.m34 * a_matrix.m43 - a_matrix.m23 * a_matrix.m32 * a_matrix.m44 + a_matrix.m22 * a_matrix.m33 * a_matrix.m44);
	tmp.m12 = invDet * (a_matrix.m14 * a_matrix.m33 * a_matrix.m42 - a_matrix.m13 * a_matrix.m34 * a_matrix.m42 - a_matrix.m14 * a_matrix.m32 * a_matrix.m43 + a_matrix.m12 * a_matrix.m34 * a_matrix.m43 + a_matrix.m13 * a_matrix.m32 * a_matrix.m44 - a_matrix.m12 * a_matrix.m33 * a_matrix.m44);
	tmp.m13 = invDet * (a_matrix.m13 * a_matrix.m24 * a_matrix.m42 - a_matrix.m14 * a_matrix.m23 * a_matrix.m42 + a_matrix.m14 * a_matrix.m22 * a_matrix.m43 - a_matrix.m12 * a_matrix.m24 * a_matrix.m43 - a_matrix.m13 * a_matrix.m22 * a_matrix.m44 + a_matrix.m12 * a_matrix.m23 * a_matrix.m44);
	tmp.m14 = invDet * (a_matrix.m14 * a_matrix.m23 * a_matrix.m32 - a_matrix.m13 * a_matrix.m24 * a_matrix.m32 - a_matrix.m14 * a_matrix.m22 * a_matrix.m33 + a_matrix.m12 * a_matrix.m24 * a_matrix.m33 + a_matrix.m13 * a_matrix.m22 * a_matrix.m34 - a_matrix.m12 * a_matrix.m23 * a_matrix.m34);
	tmp.m21 = invDet * (a_matrix.m24 * a_matrix.m33 * a_matrix.m41 - a_matrix.m23 * a_matrix.m34 * a_matrix.m41 - a_matrix.m24 * a_matrix.m31 * a_matrix.m43 + a_matrix.m21 * a_matrix.m34 * a_matrix.m43 + a_matrix.m23 * a_matrix.m31 * a_matrix.m44 - a_matrix.m21 * a_matrix.m33 * a_matrix.m44);
	tmp.m22 = invDet * (a_matrix.m13 * a_matrix.m34 * a_matrix.m41 - a_matrix.m14 * a_matrix.m33 * a_matrix.m41 + a_matrix.m14 * a_matrix.m31 * a_matrix.m43 - a_matrix.m11 * a_matrix.m34 * a_matrix.m43 - a_matrix.m13 * a_matrix.m31 * a_matrix.m44 + a_matrix.m11 * a_matrix.m33 * a_matrix.m44);
	tmp.m23 = invDet * (a_matrix.m14 * a_matrix.m23 * a_matrix.m41 - a_matrix.m13 * a_matrix.m24 * a_matrix.m41 - a_matrix.m14 * a_matrix.m21 * a_matrix.m43 + a_matrix.m11 * a_matrix.m24 * a_matrix.m43 + a_matrix.m13 * a_matrix.m21 * a_matrix.m44 - a_matrix.m11 * a_matrix.m23 * a_matrix.m44);
	tmp.m24 = invDet * (a_matrix.m13 * a_matrix.m24 * a_matrix.m31 - a_matrix.m14 * a_matrix.m23 * a_matrix.m31 + a_matrix.m14 * a_matrix.m21 * a_matrix.m33 - a_matrix.m11 * a_matrix.m24 * a_matrix.m33 - a_matrix.m13 * a_matrix.m21 * a_matrix.m34 + a_matrix.m11 * a_matrix.m23 * a_matrix.m34);
	tmp.m31 = invDet * (a_matrix.m22 * a_matrix.m34 * a_matrix.m41 - a_matrix.m24 * a_matrix.m32 * a_matrix.m41 + a_matrix.m24 * a_matrix.m31 * a_matrix.m42 - a_matrix.m21 * a_matrix.m34 * a_matrix.m42 - a_matrix.m22 * a_matrix.m31 * a_matrix.m44 + a_matrix.m21 * a_matrix.m32 * a_matrix.m44);
	tmp.m32 = invDet * (a_matrix.m14 * a_matrix.m32 * a_matrix.m41 - a_matrix.m12 * a_matrix.m34 * a_matrix.m41 - a_matrix.m14 * a_matrix.m31 * a_matrix.m42 + a_matrix.m11 * a_matrix.m34 * a_matrix.m42 + a_matrix.m12 * a_matrix.m31 * a_matrix.m44 - a_matrix.m11 * a_matrix.m32 * a_matrix.m44);
	tmp.m33 = invDet * (a_matrix.m12 * a_matrix.m24 * a_matrix.m41 - a_matrix.m14 * a_matrix.m22 * a_matrix.m41 + a_matrix.m14 * a_matrix.m21 * a_matrix.m42 - a_matrix.m11 * a_matrix.m24 * a_matrix.m42 - a_matrix.m12 * a_matrix.m21 * a_matrix.m44 + a_matrix.m11 * a_matrix.m22 * a_matrix.m44);
	tmp.m34 = invDet * (a_matrix.m14 * a_matrix.m22 * a_matrix.m31 - a_matrix.m12 * a_matrix.m24 * a_matrix.m31 - a_matrix.m14 * a_matrix.m21 * a_matrix.m32 + a_matrix.m11 * a_matrix.m24 * a_matrix.m32 + a_matrix.m12 * a_matrix.m21 * a_matrix.m34 - a_matrix.m11 * a_matrix.m22 * a_matrix.m34);
	tmp.m41 = invDet * (a_matrix.m23 * a_matrix.m32 * a_matrix.m41 - a_matrix.m22 * a_matrix.m33 * a_matrix.m41 - a_matrix.m23 * a_matrix.m31 * a_matrix.m42 + a_matrix.m21 * a_matrix.m33 * a_matrix.m42 + a_matrix.m22 * a_matrix.m31 * a_matrix.m43 - a_matrix.m21 * a_matrix.m32 * a_matrix.m43);
	tmp.m42 = invDet * (a_matrix.m12 * a_matrix.m33 * a_matrix.m41 - a_matrix.m13 * a_matrix.m32 * a_matrix.m41 + a_matrix.m13 * a_matrix.m31 * a_matrix.m42 - a_matrix.m11 * a_matrix.m33 * a_matrix.m42 - a_matrix.m12 * a_matrix.m31 * a_matrix.m43 + a_matrix.m11 * a_matrix.m32 * a_matrix.m43);
	tmp.m43 = invDet * (a_matrix.m13 * a_matrix.m22 * a_matrix.m41 - a_matrix.m12 * a_matrix.m23 * a_matrix.m41 - a_matrix.m13 * a_matrix.m21 * a_matrix.m42 + a_matrix.m11 * a_matrix.m23 * a_matrix.m42 + a_matrix.m12 * a_matrix.m21 * a_matrix.m43 - a_matrix.m11 * a_matrix.m22 * a_matrix.m43);
	tmp.m44 = invDet * (a_matrix.m12 * a_matrix.m23 * a_matrix.m31 - a_matrix.m13 * a_matrix.m22 * a_matrix.m31 + a_matrix.m13 * a_matrix.m21 * a_matrix.m32 - a_matrix.m11 * a_matrix.m23 * a_matrix.m32 - a_matrix.m12 * a_matrix.m21 * a_matrix.m33 + a_matrix.m11 * a_matrix.m22 * a_matrix.m33);

	return tmp;
}

float SMatrix4x4::Determinant(SMatrix4x4 a_matrix)
{
	float a = a_matrix.m11 * (
		(a_matrix.m22 * a_matrix.m33 * a_matrix.m44) + (a_matrix.m23 * a_matrix.m34 * a_matrix.m42) + (a_matrix.m24 * a_matrix.m32 * a_matrix.m43) -
		(a_matrix.m24 * a_matrix.m33 * a_matrix.m42) - (a_matrix.m23 * a_matrix.m32 * a_matrix.m44) - (a_matrix.m22 * a_matrix.m34 * a_matrix.m43));

	float b = a_matrix.m21 * (
		(a_matrix.m12 * a_matrix.m33 * a_matrix.m44) + (a_matrix.m32 * a_matrix.m34 * a_matrix.m42) + (a_matrix.m14 * a_matrix.m32 * a_matrix.m43) -
		(a_matrix.m14 * a_matrix.m33 * a_matrix.m42) - (a_matrix.m13 * a_matrix.m32 * a_matrix.m44) - (a_matrix.m12 * a_matrix.m34 * a_matrix.m43));

	float c = a_matrix.m31 * (
		(a_matrix.m12 * a_matrix.m23 * a_matrix.m44) + (a_matrix.m13 * a_matrix.m24 * a_matrix.m42) + (a_matrix.m14 * a_matrix.m22 * a_matrix.m43) -
		(a_matrix.m14 * a_matrix.m23 * a_matrix.m42) - (a_matrix.m13 * a_matrix.m22 * a_matrix.m44) - (a_matrix.m12 * a_matrix.m24 * a_matrix.m43));

	float d = a_matrix.m41 * (
		(a_matrix.m12 * a_matrix.m23 * a_matrix.m34) + (a_matrix.m13 * a_matrix.m24 * a_matrix.m32) + (a_matrix.m14 * a_matrix.m22 * a_matrix.m33) -
		(a_matrix.m14 * a_matrix.m23 * a_matrix.m32) - (a_matrix.m13 * a_matrix.m22 * a_matrix.m34) - (a_matrix.m12 * a_matrix.m24 * a_matrix.m33));

	return a - b + c - d;
}
