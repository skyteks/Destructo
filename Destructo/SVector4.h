#pragma once
#include <math.h>
#include <limits>

struct SVector4
{
public:
    ////=======================================================================
    //// Public Member variables
    ////=======================================================================

    /// @brief Components of the vector
    float x, y, z, w;

    ////=======================================================================
    //// Constructor / Destructor
    ////=======================================================================

    /// @brief Default Constructor.
    SVector4();

    /// @brief Constructor with arguments.
    /// @param a_x float value which will initialize the x-component of vector.
    /// @param a_y float value which will initialize the y-component of vector.
    /// @param a_z float value which will initialize the z-component of vector.
    /// @param a_w float value which will initialize the w-component of vector.
    SVector4(const float a_x, const float a_y, const float a_z, const float a_w);

    ////=======================================================================
    //// Public Member functions
    ////=======================================================================

    /// @brief Returns the vector with normalization.
    /// @return Returns the vector with length = 1.0f.
    SVector4 Normalized() const;

    /// @brief Normalizes the vector.
    void Normalize();

    /// @brief Calculates the length (magnitude) of vector.
    /// @return Returns the length of the vector.
    float Length() const;

    ////=======================================================================
    //// Operator overload
    ////=======================================================================

    /// @brief Assigns a vector.
    /// @param a_vector Vector which will be assigned.
    inline void operator=(const SVector4& a_vector);

    /// @brief Adds a vector.
    /// @param a_vector Vector which will be added.
    inline void operator+=(const SVector4& a_vector);

    /// @brief Subtracts a vector.
    /// @param a_vector Vector which will be subtracted.
    inline void operator-=(const SVector4& a_vector);

    /// @brief Multiplies a vector.
    /// @param a_vector Vector which will be multiplied.
    inline void operator*=(const SVector4& a_vector);

    /// @brief Adds a scalar.
    /// @param a_scalar Scalar which will be multiplied.
    void operator*=(const float a_scalar);



    ////=======================================================================
    //// Static Functions
    ////=======================================================================

    /// @brief Calculates the dot product of two vectors.
    /// @param a_vector Requires a normalized Vector.
    /// @param a_vector2 Requires a normalized Vector.
    /// @return Returns a float value which ranges from -1.0f to 1.0f depending on the vector direction.
    static float Dot(const SVector4& a_vector1, const SVector4& a_vector2);

    /// @brief Normalizes a vector. The length will be set to 1.0f.
    /// @param a_vector A vector as reference.
    static void Normalize(SVector4& a_vector);

    /// @brief Generates a normalized vector from another vector.
    /// @param a_vector A vector as reference.
    /// @return Returns a normalized vector.
    static SVector4 Normalized(const SVector4& a_vector);

    /// @brief Calculates the distance between two vectors.
    /// @param a_vector A vector as reference.
    /// @param a_vector2 A vector as reference.
    /// @return Returns the distance between the two passed vectors.
    static float Distance(const SVector4& a_vector1, const SVector4& a_vector2);

    ////=======================================================================
    //// Static Members
    ////=======================================================================

    static SVector4 Zero();
    static SVector4 One();
};


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
    SVector4 tmp;
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
    SVector4 tmp;
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
    SVector4 tmp;
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
    SVector4 tmp;
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
    SVector4 tmp;
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
    SVector4 tmp;
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