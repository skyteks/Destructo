#include <limits>

////=======================================================================
//// Global Operator overload
////=======================================================================
inline void SVector4::operator=(const SVector4 & a_vector)
{
    this->x = a_vector.x;
    this->y = a_vector.y;
    this->z = a_vector.z;
    this->w = a_vector.w;
}
inline void SVector4::operator+=(const SVector4 & a_vector)
{
    this->x += a_vector.x;
    this->y += a_vector.y;
    this->z += a_vector.z;
    this->w += a_vector.w;
}
inline void SVector4::operator-=(const SVector4 & a_vector)
{
    this->x -= a_vector.x;
    this->y -= a_vector.y;
    this->z -= a_vector.z;
    this->w -= a_vector.w;
}
inline void SVector4::operator*=(const SVector4 & a_vector)
{
    this->x *= a_vector.x;
    this->y *= a_vector.y;
    this->z *= a_vector.z;
    this->w *= a_vector.w;
}
inline void SVector4::operator*=(const float a_scalar)
{
    this->x *= a_scalar;
    this->y *= a_scalar;
    this->z *= a_scalar;
    this->w *= a_scalar;
}


/// @brief Adds two vectors.
/// @param a_vector A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns the sum of both vectors.

inline SVector4 operator+(const SVector4& a_vector1, const SVector4& a_vector2)
{
    SVector4 tmp = SVector4::Zero();
    tmp.x = a_vector1.x + a_vector2.x;
    tmp.y = a_vector1.y + a_vector2.y;
    tmp.z = a_vector1.z + a_vector2.z;
    tmp.w = a_vector1.w + a_vector2.w;
    return tmp;
}

/// @brief Subtracts two vectors.
/// @param a_vector A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns the subtraction of both vectors.
inline SVector4 operator-(const SVector4& a_vector1, const SVector4& a_vector2)
{
    SVector4 tmp = SVector4::Zero();
    tmp.x = a_vector1.x - a_vector2.x;
    tmp.y = a_vector1.y - a_vector2.y;
    tmp.z = a_vector1.z - a_vector2.z;
    tmp.w = a_vector1.w - a_vector2.w;
    return tmp;
}

/// @brief Multiplies two vectors.
/// @param a_vector A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns the multiplication of both vectors.
inline SVector4 operator*(const SVector4& a_vector1, const SVector4& a_vector2)
{
    SVector4 tmp = SVector4::Zero();
    tmp.x = a_vector1.x * a_vector2.x;
    tmp.y = a_vector1.y * a_vector2.y;
    tmp.z = a_vector1.z * a_vector2.z;
    tmp.w = a_vector1.w * a_vector2.w;
    return tmp;
}

/// @brief Scales a vector.
/// @param a_vector A vector as reference.
/// @param a_scalar A scalar which will be multiplied with the vector.
/// @return Returns a new sized vector.
inline SVector4 operator*(const SVector4& a_vector, const float a_scalar)
{
    SVector4 tmp = SVector4::Zero();
    tmp.x = a_vector.x * a_scalar;
    tmp.y = a_vector.y * a_scalar;
    tmp.z = a_vector.z * a_scalar;
    tmp.w = a_vector.w * a_scalar;
    return tmp;
}

/// @brief Scales a vector.
/// @param a_scalar A scalar which will be multiplied with the vector.
/// @param a_vector A vector as reference.
/// @return Returns a new sized vector.
inline SVector4 operator*(const float a_scalar, const SVector4& a_vector)
{
    SVector4 tmp = SVector4::Zero();
    tmp.x = a_vector.x * a_scalar;
    tmp.y = a_vector.y * a_scalar;
    tmp.z = a_vector.z * a_scalar;
    tmp.w = a_vector.w * a_scalar;
    return tmp;
}

/// @brief Divides a vector.
/// @param a_vector A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns the division of both vectors.
inline SVector4 operator/(const SVector4& a_vector1, const SVector4& a_vector2)
{
    SVector4 tmp = SVector4::Zero();
    tmp.x = a_vector1.x / a_vector2.x;
    tmp.y = a_vector1.y / a_vector2.y;
    tmp.z = a_vector1.z / a_vector2.z;
    tmp.w = a_vector1.w / a_vector2.w;
    return tmp;
}

/// @brief Checks for equalisation of two vectors.
/// @param a_vector A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns true if they are equal, else false.
inline bool operator==(const SVector4& a_vector1, const SVector4& a_vector2)
{
    float epsilon = std::numeric_limits<float>::epsilon();

    return (a_vector1.x - a_vector2.x < epsilon) &&
        (a_vector1.y - a_vector2.y < epsilon) &&
        (a_vector1.z - a_vector2.z < epsilon) &&
        (a_vector1.w - a_vector2.w < epsilon);
}

/// @brief Checks for non-equalisation of two vectors.
/// @param a_vector A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns true if they are not equal, else false.
inline bool operator!=(const SVector4& a_vector1, const SVector4& a_vector2)
{
    return !(a_vector1 == a_vector2);
}