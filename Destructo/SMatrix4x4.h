#pragma once
#include "SVector3.h"
#include "SVector4.h"

struct SMatrix4x4
{
public:
    float m00, m10, m20, m30;
    float m01, m11, m21, m31;
    float m02, m12, m22, m32;
    float m03, m13, m23, m33;


public:
    SMatrix4x4(
        float a_m00, float a_m10, float a_m20, float a_m30,
        float a_m01, float a_m11, float a_m21, float a_m31,
        float a_m02, float a_m12, float a_m22, float a_m32,
        float a_m03, float a_m13, float a_m23, float a_m33
    );

    SMatrix4x4(SVector4& a_r0, SVector4& a_r1, SVector4& a_r2, SVector4& a_r3);

    void SetRow(int rowIndex, SVector4& SVector4);
    SVector4 GetRow(int rowIndex) const;

    void SetColumn(int rowIndex, SVector4& SVector4);
    SVector4 GetColumn(int rowIndex) const;

    static SMatrix4x4 Identity();

    friend SMatrix4x4 operator +(SMatrix4x4& a_matrix1, SMatrix4x4& a_matrix2);
    friend SMatrix4x4 operator -(SMatrix4x4& a_matrix1, SMatrix4x4& a_matrix2);
    friend SMatrix4x4 operator *(SMatrix4x4& a_matrix1, SMatrix4x4& a_matrix2);
    friend SMatrix4x4 operator *(SMatrix4x4& a_matrix, float a_f);
    friend SMatrix4x4 operator *(float a_f, SMatrix4x4& a_matrix);
    friend SVector4 operator *(SMatrix4x4& a_matrix, SVector3& a_vector);
    friend SVector4 operator *(SVector3& a_vector, SMatrix4x4& a_matrix);
    friend bool operator ==(SMatrix4x4& a_matrix1, SMatrix4x4& a_matrix2);
    friend bool operator !=(SMatrix4x4& a_matrix1, SMatrix4x4& a_matrix2);

    static SMatrix4x4 Transpose(SMatrix4x4& a_matrix);

    static SMatrix4x4 Scale(SVector3& a_vector);
    static SMatrix4x4 Translation(SVector3& a_vector);
    static SMatrix4x4 RotationX(float a_f);
    static SMatrix4x4 RotationY(float a_f);
    static SMatrix4x4 RotationZ(float a_f);

    static SMatrix4x4 Invert(SMatrix4x4& a_matrix);

    static float Determinant(SMatrix4x4& a_matrix);
};