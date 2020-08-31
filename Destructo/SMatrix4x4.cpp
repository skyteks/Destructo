#include "SMatrix4x4.h"
#include <limits>
#include <stdexcept>

//SMatrix4x4::SMatrix4x4() :
//    m00(1.0f), m01(0.0f), m02(0.0f), m03(0.0f),
//    m10(0.0f), m11(1.0f), m12(0.0f), m13(0.0f),
//    m20(0.0f), m21(0.0f), m22(1.0f), m23(0.0f),
//    m30(0.0f), m31(0.0f), m32(0.0f), m33(1.0f)
//{
//}


SMatrix4x4::SMatrix4x4(
    float a_m00, float a_m10, float a_m20, float a_m30,
    float a_m01, float a_m11, float a_m21, float a_m31,
    float a_m02, float a_m12, float a_m22, float a_m32,
    float a_m03, float a_m13, float a_m23, float a_m33) :
    m00(a_m00), m10(a_m10), m20(a_m20), m30(a_m30),
    m01(a_m01), m11(a_m11), m21(a_m21), m31(a_m31),
    m02(a_m02), m12(a_m12), m22(a_m22), m32(a_m32),
    m03(a_m03), m13(a_m13), m23(a_m23), m33(a_m33)
{
}


SMatrix4x4::SMatrix4x4(SVector4& a_column0, SVector4& a_column1, SVector4& a_column2, SVector4& a_column3) :
    m00(a_column0.x), m10(a_column1.x), m20(a_column2.x), m30(a_column3.x),
    m01(a_column0.y), m11(a_column1.y), m21(a_column2.y), m31(a_column3.y),
    m02(a_column0.z), m12(a_column1.z), m22(a_column2.z), m32(a_column3.z),
    m03(a_column0.w), m13(a_column1.w), m23(a_column2.w), m33(a_column3.w)
{
}


void SMatrix4x4::SetRow(int a_rowIndex, SVector4& a_vector4)
{
    switch (a_rowIndex)
    {
        case 0:
            m00 = a_vector4.x;
            m10 = a_vector4.y;
            m20 = a_vector4.z;
            m30 = a_vector4.w;
            break;
        case 1:
            m01 = a_vector4.x;
            m11 = a_vector4.y;
            m21 = a_vector4.z;
            m31 = a_vector4.w;
            break;
        case 2:
            m02 = a_vector4.x;
            m12 = a_vector4.y;
            m22 = a_vector4.z;
            m32 = a_vector4.w;
            break;
        case 3:
            m03 = a_vector4.x;
            m13 = a_vector4.y;
            m23 = a_vector4.z;
            m33 = a_vector4.w;
            break;
        default:
            throw std::out_of_range("row does not exist");
    }
}


SVector4 SMatrix4x4::GetRow(int rowIndex) const
{
    switch (rowIndex)
    {
        case 0:
            return SVector4(m00, m10, m20, m30);
        case 1:
            return SVector4(m01, m11, m21, m31);
        case 2:
            return SVector4(m02, m12, m22, m32);
        case 3:
            return SVector4(m03, m13, m23, m33);
        default:
            throw std::out_of_range("row does not exist");
    }
}


void SMatrix4x4::SetColumn(int rowIndex, SVector4& SVector4)
{
    switch (rowIndex)
    {
        case 0:
            m00 = SVector4.x;
            m01 = SVector4.y;
            m02 = SVector4.z;
            m03 = SVector4.w;
            break;
        case 1:
            m10 = SVector4.x;
            m11 = SVector4.y;
            m12 = SVector4.z;
            m13 = SVector4.w;
            break;
        case 2:
            m20 = SVector4.x;
            m21 = SVector4.y;
            m22 = SVector4.z;
            m23 = SVector4.w;
            break;
        case 3:
            m30 = SVector4.x;
            m31 = SVector4.y;
            m32 = SVector4.z;
            m33 = SVector4.w;
            break;
        default:
            throw std::out_of_range("row does not exist");
    }
}


SVector4 SMatrix4x4::GetColumn(int rowIndex) const
{
    switch (rowIndex)
    {
        case 0:
            return SVector4(m00, m01, m02, m03);
        case 1:
            return SVector4(m10, m11, m12, m13);
        case 2:
            return SVector4(m20, m21, m22, m23);
        case 3:
            return SVector4(m30, m31, m32, m33);
        default:
            throw std::out_of_range("row does not exist");
    }
}


SMatrix4x4 SMatrix4x4::Identity()
{
    return SMatrix4x4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
}


SMatrix4x4 operator +(SMatrix4x4& a_matrix1, SMatrix4x4& a_matrix2)
{
    return SMatrix4x4(
        a_matrix1.m00 + a_matrix2.m00, a_matrix1.m10 + a_matrix2.m10, a_matrix1.m20 + a_matrix2.m20, a_matrix1.m30 + a_matrix2.m30,
        a_matrix1.m01 + a_matrix2.m01, a_matrix1.m11 + a_matrix2.m11, a_matrix1.m21 + a_matrix2.m21, a_matrix1.m31 + a_matrix2.m31,
        a_matrix1.m02 + a_matrix2.m02, a_matrix1.m12 + a_matrix2.m12, a_matrix1.m22 + a_matrix2.m22, a_matrix1.m32 + a_matrix2.m32,
        a_matrix1.m03 + a_matrix2.m03, a_matrix1.m13 + a_matrix2.m13, a_matrix1.m23 + a_matrix2.m23, a_matrix1.m33 + a_matrix2.m33);
}


SMatrix4x4 operator -(SMatrix4x4& a_matrix1, SMatrix4x4& a_matrix2)
{
    return SMatrix4x4(
        a_matrix1.m00 - a_matrix2.m00, a_matrix1.m10 - a_matrix2.m10, a_matrix1.m20 - a_matrix2.m20, a_matrix1.m30 - a_matrix2.m30,
        a_matrix1.m01 - a_matrix2.m01, a_matrix1.m11 - a_matrix2.m11, a_matrix1.m21 - a_matrix2.m21, a_matrix1.m31 - a_matrix2.m31,
        a_matrix1.m02 - a_matrix2.m02, a_matrix1.m12 - a_matrix2.m12, a_matrix1.m22 - a_matrix2.m22, a_matrix1.m32 - a_matrix2.m32,
        a_matrix1.m03 - a_matrix2.m03, a_matrix1.m13 - a_matrix2.m13, a_matrix1.m23 - a_matrix2.m23, a_matrix1.m33 - a_matrix2.m33);
}


SMatrix4x4 operator *(SMatrix4x4& a_matrix1, SMatrix4x4& a_matrix2)
{
    return SMatrix4x4(
        a_matrix1.m00 * a_matrix2.m00 + a_matrix1.m01 * a_matrix2.m10 + a_matrix1.m02 * a_matrix2.m20 + a_matrix1.m03 * a_matrix2.m30,
        a_matrix1.m10 * a_matrix2.m00 + a_matrix1.m11 * a_matrix2.m10 + a_matrix1.m12 * a_matrix2.m20 + a_matrix1.m13 * a_matrix2.m30,
        a_matrix1.m20 * a_matrix2.m00 + a_matrix1.m21 * a_matrix2.m10 + a_matrix1.m22 * a_matrix2.m20 + a_matrix1.m23 * a_matrix2.m30,
        a_matrix1.m30 * a_matrix2.m00 + a_matrix1.m31 * a_matrix2.m10 + a_matrix1.m32 * a_matrix2.m20 + a_matrix1.m33 * a_matrix2.m30,
        a_matrix1.m00 * a_matrix2.m01 + a_matrix1.m01 * a_matrix2.m11 + a_matrix1.m02 * a_matrix2.m21 + a_matrix1.m03 * a_matrix2.m31,
        a_matrix1.m10 * a_matrix2.m01 + a_matrix1.m11 * a_matrix2.m11 + a_matrix1.m12 * a_matrix2.m21 + a_matrix1.m13 * a_matrix2.m31,
        a_matrix1.m20 * a_matrix2.m01 + a_matrix1.m21 * a_matrix2.m11 + a_matrix1.m22 * a_matrix2.m21 + a_matrix1.m23 * a_matrix2.m31,
        a_matrix1.m30 * a_matrix2.m01 + a_matrix1.m31 * a_matrix2.m11 + a_matrix1.m32 * a_matrix2.m21 + a_matrix1.m33 * a_matrix2.m31,
        a_matrix1.m00 * a_matrix2.m02 + a_matrix1.m01 * a_matrix2.m12 + a_matrix1.m02 * a_matrix2.m22 + a_matrix1.m03 * a_matrix2.m32,
        a_matrix1.m10 * a_matrix2.m02 + a_matrix1.m11 * a_matrix2.m12 + a_matrix1.m12 * a_matrix2.m22 + a_matrix1.m13 * a_matrix2.m32,
        a_matrix1.m20 * a_matrix2.m02 + a_matrix1.m21 * a_matrix2.m12 + a_matrix1.m22 * a_matrix2.m22 + a_matrix1.m23 * a_matrix2.m32,
        a_matrix1.m30 * a_matrix2.m02 + a_matrix1.m31 * a_matrix2.m12 + a_matrix1.m32 * a_matrix2.m22 + a_matrix1.m33 * a_matrix2.m32,
        a_matrix1.m00 * a_matrix2.m03 + a_matrix1.m01 * a_matrix2.m13 + a_matrix1.m02 * a_matrix2.m23 + a_matrix1.m03 * a_matrix2.m33,
        a_matrix1.m10 * a_matrix2.m03 + a_matrix1.m11 * a_matrix2.m13 + a_matrix1.m12 * a_matrix2.m23 + a_matrix1.m13 * a_matrix2.m33,
        a_matrix1.m20 * a_matrix2.m03 + a_matrix1.m21 * a_matrix2.m13 + a_matrix1.m22 * a_matrix2.m23 + a_matrix1.m23 * a_matrix2.m33,
        a_matrix1.m30 * a_matrix2.m03 + a_matrix1.m31 * a_matrix2.m13 + a_matrix1.m32 * a_matrix2.m23 + a_matrix1.m33 * a_matrix2.m33);
}


SMatrix4x4 operator *(SMatrix4x4& a_matrix, float a_f)
{
    return SMatrix4x4(
        a_matrix.m00 * a_f, a_matrix.m10 * a_f, a_matrix.m20 * a_f, a_matrix.m30 * a_f,
        a_matrix.m01 * a_f, a_matrix.m11 * a_f, a_matrix.m21 * a_f, a_matrix.m31 * a_f,
        a_matrix.m02 * a_f, a_matrix.m12 * a_f, a_matrix.m22 * a_f, a_matrix.m32 * a_f,
        a_matrix.m03 * a_f, a_matrix.m13 * a_f, a_matrix.m23 * a_f, a_matrix.m33 * a_f);
}


SMatrix4x4 operator *(float a_f, SMatrix4x4& a_matrix)
{
    return a_matrix * a_f;
}


SVector4 operator *(SMatrix4x4& a_matrix, SVector3& a_vector)
{
    SVector4 tmp = SVector4(0.0f, 0.0f, 0.0f, 0.0f);

    tmp.x = a_matrix.m00 * a_vector.x + a_matrix.m10 * a_vector.y + a_matrix.m20 * a_vector.z + a_matrix.m30 * 1.0f;
    tmp.y = a_matrix.m01 * a_vector.x + a_matrix.m11 * a_vector.y + a_matrix.m21 * a_vector.z + a_matrix.m31 * 1.0f;
    tmp.z = a_matrix.m02 * a_vector.x + a_matrix.m12 * a_vector.y + a_matrix.m22 * a_vector.z + a_matrix.m32 * 1.0f;
    tmp.w = a_matrix.m03 * a_vector.x + a_matrix.m13 * a_vector.y + a_matrix.m23 * a_vector.z + a_matrix.m33 * 1.0f;

    return tmp;
}


SVector4 operator *(SVector3& a_vector, SMatrix4x4& a_matrix)
{
    return a_matrix * a_vector;
}


bool operator ==(SMatrix4x4& a_matrix1, SMatrix4x4& a_matrix2)
{
    float epsilon = std::numeric_limits<float>::epsilon();
    return (
        (a_matrix1.m00 >= a_matrix2.m00 - epsilon && a_matrix1.m00 <= a_matrix2.m00 + epsilon) &&
        (a_matrix1.m10 >= a_matrix2.m10 - epsilon && a_matrix1.m10 <= a_matrix2.m10 + epsilon) &&
        (a_matrix1.m20 >= a_matrix2.m20 - epsilon && a_matrix1.m20 <= a_matrix2.m20 + epsilon) &&
        (a_matrix1.m30 >= a_matrix2.m30 - epsilon && a_matrix1.m30 <= a_matrix2.m30 + epsilon) &&
        (a_matrix1.m01 >= a_matrix2.m01 - epsilon && a_matrix1.m01 <= a_matrix2.m01 + epsilon) &&
        (a_matrix1.m11 >= a_matrix2.m11 - epsilon && a_matrix1.m11 <= a_matrix2.m11 + epsilon) &&
        (a_matrix1.m21 >= a_matrix2.m21 - epsilon && a_matrix1.m21 <= a_matrix2.m21 + epsilon) &&
        (a_matrix1.m31 >= a_matrix2.m31 - epsilon && a_matrix1.m31 <= a_matrix2.m31 + epsilon) &&
        (a_matrix1.m02 >= a_matrix2.m02 - epsilon && a_matrix1.m02 <= a_matrix2.m02 + epsilon) &&
        (a_matrix1.m12 >= a_matrix2.m12 - epsilon && a_matrix1.m12 <= a_matrix2.m12 + epsilon) &&
        (a_matrix1.m22 >= a_matrix2.m22 - epsilon && a_matrix1.m22 <= a_matrix2.m22 + epsilon) &&
        (a_matrix1.m32 >= a_matrix2.m32 - epsilon && a_matrix1.m32 <= a_matrix2.m32 + epsilon) &&
        (a_matrix1.m03 >= a_matrix2.m03 - epsilon && a_matrix1.m03 <= a_matrix2.m03 + epsilon) &&
        (a_matrix1.m13 >= a_matrix2.m13 - epsilon && a_matrix1.m13 <= a_matrix2.m13 + epsilon) &&
        (a_matrix1.m23 >= a_matrix2.m23 - epsilon && a_matrix1.m23 <= a_matrix2.m23 + epsilon) &&
        (a_matrix1.m33 >= a_matrix2.m33 - epsilon && a_matrix1.m33 <= a_matrix2.m33 + epsilon));
}


bool operator !=(SMatrix4x4& a_matrix1, SMatrix4x4& a_matrix2)
{
    return !(a_matrix1 == a_matrix2);
}


SMatrix4x4 SMatrix4x4::Transpose(SMatrix4x4& a_matrix)
{
    return SMatrix4x4(
        a_matrix.m00, a_matrix.m01, a_matrix.m02, a_matrix.m03,
        a_matrix.m10, a_matrix.m11, a_matrix.m12, a_matrix.m13,
        a_matrix.m20, a_matrix.m21, a_matrix.m22, a_matrix.m23,
        a_matrix.m30, a_matrix.m31, a_matrix.m32, a_matrix.m33
    );
}


SMatrix4x4 SMatrix4x4::Scale(SVector3& a_vector)
{
    SMatrix4x4 tmp = Identity();

    tmp.m00 = a_vector.x;
    tmp.m11 = a_vector.y;
    tmp.m22 = a_vector.z;

    return tmp;
}


SMatrix4x4 SMatrix4x4::Translation(SVector3& a_vector)
{
    SMatrix4x4 tmp = Identity();

    tmp.m03 = a_vector.x;
    tmp.m13 = a_vector.y;
    tmp.m23 = a_vector.z;

    return tmp;
}


SMatrix4x4 SMatrix4x4::RotationX(float a_f)
{
    SMatrix4x4 tmp = Identity();

    tmp.m11 = tmp.m22 = static_cast<float>(cos(a_f));
    tmp.m21 = static_cast<float>(sin(a_f));
    tmp.m12 = -tmp.m21;

    return tmp;
}


SMatrix4x4 SMatrix4x4::RotationY(float a_f)
{
    SMatrix4x4 tmp = Identity();

    tmp.m00 = tmp.m22 = static_cast<float>(cos(a_f));
    tmp.m02 = static_cast<float>(sin(a_f));
    tmp.m20 = -tmp.m02;

    return tmp;
}


SMatrix4x4 SMatrix4x4::RotationZ(float a_f)
{
    SMatrix4x4 tmp = Identity();

    tmp.m00 = tmp.m11 = cos(a_f);
    tmp.m10 = -sin(a_f);
    tmp.m01 = -tmp.m10;

    return tmp;
}


SMatrix4x4 SMatrix4x4::Invert(SMatrix4x4& a_matrix)
{
    SMatrix4x4 tmp = Identity();

    float invDet = 1.0f / SMatrix4x4::Determinant(a_matrix);

    tmp.m00 = invDet * (a_matrix.m21 * a_matrix.m32 * a_matrix.m13 - a_matrix.m31 * a_matrix.m22 * a_matrix.m13 + a_matrix.m31 * a_matrix.m12 * a_matrix.m23 - a_matrix.m11 * a_matrix.m32 * a_matrix.m23 - a_matrix.m21 * a_matrix.m12 * a_matrix.m33 + a_matrix.m11 * a_matrix.m22 * a_matrix.m33);
    tmp.m10 = invDet * (a_matrix.m30 * a_matrix.m22 * a_matrix.m13 - a_matrix.m20 * a_matrix.m32 * a_matrix.m13 - a_matrix.m30 * a_matrix.m12 * a_matrix.m23 + a_matrix.m10 * a_matrix.m32 * a_matrix.m23 + a_matrix.m20 * a_matrix.m12 * a_matrix.m33 - a_matrix.m10 * a_matrix.m22 * a_matrix.m33);
    tmp.m20 = invDet * (a_matrix.m20 * a_matrix.m31 * a_matrix.m13 - a_matrix.m30 * a_matrix.m21 * a_matrix.m13 + a_matrix.m30 * a_matrix.m11 * a_matrix.m23 - a_matrix.m10 * a_matrix.m31 * a_matrix.m23 - a_matrix.m20 * a_matrix.m11 * a_matrix.m33 + a_matrix.m10 * a_matrix.m21 * a_matrix.m33);
    tmp.m30 = invDet * (a_matrix.m30 * a_matrix.m21 * a_matrix.m12 - a_matrix.m20 * a_matrix.m31 * a_matrix.m12 - a_matrix.m30 * a_matrix.m11 * a_matrix.m22 + a_matrix.m10 * a_matrix.m31 * a_matrix.m22 + a_matrix.m20 * a_matrix.m11 * a_matrix.m32 - a_matrix.m10 * a_matrix.m21 * a_matrix.m32);
    tmp.m01 = invDet * (a_matrix.m31 * a_matrix.m22 * a_matrix.m03 - a_matrix.m21 * a_matrix.m32 * a_matrix.m03 - a_matrix.m31 * a_matrix.m02 * a_matrix.m23 + a_matrix.m01 * a_matrix.m32 * a_matrix.m23 + a_matrix.m21 * a_matrix.m02 * a_matrix.m33 - a_matrix.m01 * a_matrix.m22 * a_matrix.m33);
    tmp.m11 = invDet * (a_matrix.m20 * a_matrix.m32 * a_matrix.m03 - a_matrix.m30 * a_matrix.m22 * a_matrix.m03 + a_matrix.m30 * a_matrix.m02 * a_matrix.m23 - a_matrix.m00 * a_matrix.m32 * a_matrix.m23 - a_matrix.m20 * a_matrix.m02 * a_matrix.m33 + a_matrix.m00 * a_matrix.m22 * a_matrix.m33);
    tmp.m21 = invDet * (a_matrix.m30 * a_matrix.m21 * a_matrix.m03 - a_matrix.m20 * a_matrix.m31 * a_matrix.m03 - a_matrix.m30 * a_matrix.m01 * a_matrix.m23 + a_matrix.m00 * a_matrix.m31 * a_matrix.m23 + a_matrix.m20 * a_matrix.m01 * a_matrix.m33 - a_matrix.m00 * a_matrix.m21 * a_matrix.m33);
    tmp.m31 = invDet * (a_matrix.m20 * a_matrix.m31 * a_matrix.m02 - a_matrix.m30 * a_matrix.m21 * a_matrix.m02 + a_matrix.m30 * a_matrix.m01 * a_matrix.m22 - a_matrix.m00 * a_matrix.m31 * a_matrix.m22 - a_matrix.m20 * a_matrix.m01 * a_matrix.m32 + a_matrix.m00 * a_matrix.m21 * a_matrix.m32);
    tmp.m02 = invDet * (a_matrix.m11 * a_matrix.m32 * a_matrix.m03 - a_matrix.m31 * a_matrix.m12 * a_matrix.m03 + a_matrix.m31 * a_matrix.m02 * a_matrix.m13 - a_matrix.m01 * a_matrix.m32 * a_matrix.m13 - a_matrix.m11 * a_matrix.m02 * a_matrix.m33 + a_matrix.m01 * a_matrix.m12 * a_matrix.m33);
    tmp.m12 = invDet * (a_matrix.m30 * a_matrix.m12 * a_matrix.m03 - a_matrix.m10 * a_matrix.m32 * a_matrix.m03 - a_matrix.m30 * a_matrix.m02 * a_matrix.m13 + a_matrix.m00 * a_matrix.m32 * a_matrix.m13 + a_matrix.m10 * a_matrix.m02 * a_matrix.m33 - a_matrix.m00 * a_matrix.m12 * a_matrix.m33);
    tmp.m22 = invDet * (a_matrix.m10 * a_matrix.m31 * a_matrix.m03 - a_matrix.m30 * a_matrix.m11 * a_matrix.m03 + a_matrix.m30 * a_matrix.m01 * a_matrix.m13 - a_matrix.m00 * a_matrix.m31 * a_matrix.m13 - a_matrix.m10 * a_matrix.m01 * a_matrix.m33 + a_matrix.m00 * a_matrix.m11 * a_matrix.m33);
    tmp.m32 = invDet * (a_matrix.m30 * a_matrix.m11 * a_matrix.m02 - a_matrix.m10 * a_matrix.m31 * a_matrix.m02 - a_matrix.m30 * a_matrix.m01 * a_matrix.m12 + a_matrix.m00 * a_matrix.m31 * a_matrix.m12 + a_matrix.m10 * a_matrix.m01 * a_matrix.m32 - a_matrix.m00 * a_matrix.m11 * a_matrix.m32);
    tmp.m03 = invDet * (a_matrix.m21 * a_matrix.m12 * a_matrix.m03 - a_matrix.m11 * a_matrix.m22 * a_matrix.m03 - a_matrix.m21 * a_matrix.m02 * a_matrix.m13 + a_matrix.m01 * a_matrix.m22 * a_matrix.m13 + a_matrix.m11 * a_matrix.m02 * a_matrix.m23 - a_matrix.m01 * a_matrix.m12 * a_matrix.m23);
    tmp.m13 = invDet * (a_matrix.m10 * a_matrix.m22 * a_matrix.m03 - a_matrix.m20 * a_matrix.m12 * a_matrix.m03 + a_matrix.m20 * a_matrix.m02 * a_matrix.m13 - a_matrix.m00 * a_matrix.m22 * a_matrix.m13 - a_matrix.m10 * a_matrix.m02 * a_matrix.m23 + a_matrix.m00 * a_matrix.m12 * a_matrix.m23);
    tmp.m23 = invDet * (a_matrix.m20 * a_matrix.m11 * a_matrix.m03 - a_matrix.m10 * a_matrix.m21 * a_matrix.m03 - a_matrix.m20 * a_matrix.m01 * a_matrix.m13 + a_matrix.m00 * a_matrix.m21 * a_matrix.m13 + a_matrix.m10 * a_matrix.m01 * a_matrix.m23 - a_matrix.m00 * a_matrix.m11 * a_matrix.m23);
    tmp.m33 = invDet * (a_matrix.m10 * a_matrix.m21 * a_matrix.m02 - a_matrix.m20 * a_matrix.m11 * a_matrix.m02 + a_matrix.m20 * a_matrix.m01 * a_matrix.m12 - a_matrix.m00 * a_matrix.m21 * a_matrix.m12 - a_matrix.m10 * a_matrix.m01 * a_matrix.m22 + a_matrix.m00 * a_matrix.m11 * a_matrix.m22);

    return tmp;
}


float SMatrix4x4::Determinant(SMatrix4x4& a_matrix)
{
    float determinant =
        a_matrix.m03 * a_matrix.m12 * a_matrix.m21 * a_matrix.m30 - a_matrix.m02 * a_matrix.m13 * a_matrix.m21 * a_matrix.m30 -
        a_matrix.m03 * a_matrix.m11 * a_matrix.m22 * a_matrix.m30 + a_matrix.m01 * a_matrix.m13 * a_matrix.m22 * a_matrix.m30 +
        a_matrix.m02 * a_matrix.m11 * a_matrix.m23 * a_matrix.m30 - a_matrix.m01 * a_matrix.m12 * a_matrix.m23 * a_matrix.m30 -
        a_matrix.m03 * a_matrix.m12 * a_matrix.m20 * a_matrix.m31 + a_matrix.m02 * a_matrix.m13 * a_matrix.m20 * a_matrix.m31 +
        a_matrix.m03 * a_matrix.m10 * a_matrix.m22 * a_matrix.m31 - a_matrix.m00 * a_matrix.m13 * a_matrix.m22 * a_matrix.m31 -
        a_matrix.m02 * a_matrix.m10 * a_matrix.m23 * a_matrix.m31 + a_matrix.m00 * a_matrix.m12 * a_matrix.m23 * a_matrix.m31 +
        a_matrix.m03 * a_matrix.m11 * a_matrix.m20 * a_matrix.m32 - a_matrix.m01 * a_matrix.m13 * a_matrix.m20 * a_matrix.m32 -
        a_matrix.m03 * a_matrix.m10 * a_matrix.m21 * a_matrix.m32 + a_matrix.m00 * a_matrix.m13 * a_matrix.m21 * a_matrix.m32 +
        a_matrix.m01 * a_matrix.m10 * a_matrix.m23 * a_matrix.m32 - a_matrix.m00 * a_matrix.m11 * a_matrix.m23 * a_matrix.m32 -
        a_matrix.m02 * a_matrix.m11 * a_matrix.m20 * a_matrix.m33 + a_matrix.m01 * a_matrix.m12 * a_matrix.m20 * a_matrix.m33 +
        a_matrix.m02 * a_matrix.m10 * a_matrix.m21 * a_matrix.m33 - a_matrix.m00 * a_matrix.m12 * a_matrix.m21 * a_matrix.m33 -
        a_matrix.m01 * a_matrix.m10 * a_matrix.m22 * a_matrix.m33 + a_matrix.m00 * a_matrix.m11 * a_matrix.m22 * a_matrix.m33;
    /*
    float a = a_matrix.m00 * (
        (a_matrix.m11 * a_matrix.m22 * a_matrix.m33) + (a_matrix.m21 * a_matrix.m32 * a_matrix.m13) + (a_matrix.m31 * a_matrix.m12 * a_matrix.m23) -
        (a_matrix.m31 * a_matrix.m22 * a_matrix.m13) - (a_matrix.m21 * a_matrix.m12 * a_matrix.m33) - (a_matrix.m11 * a_matrix.m32 * a_matrix.m23));
    float b = a_matrix.m01 * (
        (a_matrix.m10 * a_matrix.m22 * a_matrix.m33) + (a_matrix.m12 * a_matrix.m32 * a_matrix.m13) + (a_matrix.m30 * a_matrix.m12 * a_matrix.m23) -
        (a_matrix.m30 * a_matrix.m22 * a_matrix.m13) - (a_matrix.m20 * a_matrix.m12 * a_matrix.m33) - (a_matrix.m10 * a_matrix.m32 * a_matrix.m23));
    float c = a_matrix.m02 * (
        (a_matrix.m10 * a_matrix.m21 * a_matrix.m33) + (a_matrix.m20 * a_matrix.m31 * a_matrix.m13) + (a_matrix.m30 * a_matrix.m11 * a_matrix.m23) -
        (a_matrix.m30 * a_matrix.m21 * a_matrix.m13) - (a_matrix.m20 * a_matrix.m11 * a_matrix.m33) - (a_matrix.m10 * a_matrix.m31 * a_matrix.m23));
    float d = a_matrix.m03 * (
        (a_matrix.m10 * a_matrix.m21 * a_matrix.m32) + (a_matrix.m20 * a_matrix.m31 * a_matrix.m12) + (a_matrix.m30 * a_matrix.m11 * a_matrix.m22) -
        (a_matrix.m30 * a_matrix.m21 * a_matrix.m12) - (a_matrix.m20 * a_matrix.m11 * a_matrix.m32) - (a_matrix.m10 * a_matrix.m31 * a_matrix.m22));

    float determinant_old = a - b + c - d;// wrong
    */
    return determinant;
}