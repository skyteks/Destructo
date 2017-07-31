#pragma once
#include "SVector3.h"
#include "SVector4.h"


struct SMatrix4x4
{
public:
    float m11, m12, m13, m14;
    float m21, m22, m23, m24;
    float m31, m32, m33, m34;
    float m41, m42, m43, m44;


public:
    //SMatrix4x4();
    SMatrix4x4(
        float a_m11, float a_m12, float a_m13, float a_m14,
        float a_m21, float a_m22, float a_m23, float a_m24,
        float a_m31, float a_m32, float a_m33, float a_m34,
        float a_m41, float a_m42, float a_m43, float a_m44);

    static SMatrix4x4 Identity();

    friend SMatrix4x4 operator +(SMatrix4x4 a_matrix1, SMatrix4x4 a_matrix2);
    friend SMatrix4x4 operator -(SMatrix4x4 a_matrix1, SMatrix4x4 a_matrix2);
    friend SMatrix4x4 operator *(SMatrix4x4 a_matrix1, SMatrix4x4 a_matrix2);
    friend SMatrix4x4 operator *(SMatrix4x4 a_matrix, float a_f);
    friend SMatrix4x4 operator *(float a_f, SMatrix4x4 a_matrix);
    friend SVector4 operator *(SMatrix4x4 a_matrix, SVector3 a_vector);
    friend SVector4 operator *(SVector3 a_vector, SMatrix4x4 a_matrix);
    friend bool operator ==(SMatrix4x4 a_matrix1, SMatrix4x4 a_matrix2);
    friend bool operator !=(SMatrix4x4 a_matrix1, SMatrix4x4 a_matrix2);

    static SMatrix4x4 Transpose(SMatrix4x4 a_matrix);

    static SMatrix4x4 Scale(SVector3 a_vector);
    static SMatrix4x4 Translation(SVector3 a_vector);
    static SMatrix4x4 RotationX(float a_f);
    static SMatrix4x4 RotationY(float a_f);
    static SMatrix4x4 RotationZ(float a_f);

    static SMatrix4x4 Invert(SMatrix4x4 a_matrix);

    static float Determinant(SMatrix4x4 a_matrix);
};

