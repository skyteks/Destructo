#pragma once
#include "SVector3.h"

struct SVertex
{
public:
    SVector3 m_coord;

    float m_u;
    float m_v;
    float m_r;
    float m_g;
    float m_b;
    float m_a;

    SVertex()
        : m_coord(SVector3::Zero())
        , m_u(0.0f)
        , m_v(0.0f)
        , m_r(0.0f)
        , m_g(0.0f)
        , m_b(0.0f)
        , m_a(0.0f)
    {
    }

    SVertex(float a_x, float a_y, float a_z, float a_u, float a_v, float a_r, float a_g, float a_b, float a_a)
        : m_coord(a_x, a_y, a_z)
        , m_u(a_u)
        , m_v(a_v)
        , m_r(a_r)
        , m_g(a_g)
        , m_b(a_b)
        , m_a(a_a)
    {
    }
};