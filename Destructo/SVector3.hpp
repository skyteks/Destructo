#include <limits>


////=======================================================================
//// Global Operator overload
////=======================================================================
inline void SVector3::operator=(const SVector3& a_vector2)
{
    this->x = a_vector2.x;
    this->y = a_vector2.y;
    this->z = a_vector2.z;
}
inline void SVector3::operator+=(const SVector3& a_vector2)
{
    this->x += a_vector2.x;
    this->y += a_vector2.y;
    this->z += a_vector2.z;
}
inline void SVector3::operator-=(const SVector3& a_vector2)
{
    this->x -= a_vector2.x;
    this->y -= a_vector2.y;
    this->z -= a_vector2.z;
}
inline void SVector3::operator*=(const SVector3& a_vector2)
{
    this->x *= a_vector2.x;
    this->y *= a_vector2.y;
    this->z *= a_vector2.z;
}
inline void SVector3::operator*=(const float a_scalar)
{
    this->x *= a_scalar;
    this->y *= a_scalar;
    this->z *= a_scalar;
}


/// @brief Adds two vectors.
/// @param a_vector1 A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns the sum of both vectors.

inline SVector3 operator+(const SVector3& a_vector1, const SVector3& a_vector2)
{
    SVector3 tmp = SVector3::Zero();
    tmp.x = a_vector1.x + a_vector2.x;
    tmp.y = a_vector1.y + a_vector2.y;
    tmp.z = a_vector1.z + a_vector2.z;
    return tmp;
}

/// @brief Subtracts two vectors.
/// @param a_vector1 A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns the subtraction of both vectors.
inline SVector3 operator-(const SVector3& a_vector1, const SVector3& a_vector2)
{
    SVector3 tmp = SVector3::Zero();
    tmp.x = a_vector1.x - a_vector2.x;
    tmp.y = a_vector1.y - a_vector2.y;
    tmp.z = a_vector1.z - a_vector2.z;
    return tmp;
}

/// @brief Multiplies two vectors.
/// @param a_vector1 A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns the multiplication of both vectors.
inline SVector3 operator*(const SVector3& a_vector1, const SVector3& a_vector2)
{
    SVector3 tmp = SVector3::Zero();
    tmp.x = a_vector1.x * a_vector2.x;
    tmp.y = a_vector1.y * a_vector2.y;
    tmp.z = a_vector1.z * a_vector2.z;
    return tmp;
}

/// @brief Scales a vector.
/// @param a_vector1 A vector as reference.
/// @param a_scalar A scalar which will be multiplied with the vector.
/// @return Returns a new sized vector.
inline SVector3 operator*(const SVector3& a_vector1, const float a_scalar)
{
    SVector3 tmp = SVector3::Zero();
    tmp.x = a_vector1.x * a_scalar;
    tmp.y = a_vector1.y * a_scalar;
    tmp.z = a_vector1.z * a_scalar;
    return tmp;
}

/// @brief Scales a vector.
/// @param a_scalar A scalar which will be multiplied with the vector.
/// @param a_vector1 A vector as reference.
/// @return Returns a new sized vector.
inline SVector3 operator*(const float a_scalar, const SVector3& a_vector1)
{
    SVector3 tmp = SVector3::Zero();
    tmp.x = a_vector1.x * a_scalar;
    tmp.y = a_vector1.y * a_scalar;
    tmp.z = a_vector1.z * a_scalar;
    return tmp;
}

/// @brief Divides a vector.
/// @param a_vector1 A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns the division of both vectors.
inline SVector3 operator/(const SVector3& a_vector1, const SVector3& a_vector2)
{
    SVector3 tmp = SVector3::Zero();
    tmp.x = a_vector1.x / a_vector2.x;
    tmp.y = a_vector1.y / a_vector2.y;
    tmp.z = a_vector1.z / a_vector2.z;
    return tmp;
}

/// @brief Checks for equalisation of two vectors.
/// @param a_vector1 A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns true if they are equal, else false.
inline bool operator==(const SVector3& a_vector1, const SVector3& a_vector2)
{
    float epsilon = std::numeric_limits<float>::epsilon();

    return (a_vector1.x - a_vector2.x < epsilon) &&
        (a_vector1.y - a_vector2.y < epsilon) &&
        (a_vector1.z - a_vector2.z < epsilon);
}

/// @brief Checks for non-equalisation of two vectors.
/// @param a_vector1 A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns true if they are not equal, else false.
inline bool operator!=(const SVector3& a_vector1, const SVector3& a_vector2)
{
    return !(a_vector1 == a_vector2);
}