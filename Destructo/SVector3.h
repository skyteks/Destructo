#pragma once
#include <math.h>
#include <limits>

struct SVector3
{
public:
    ////=======================================================================
    //// Public Member variables
    ////=======================================================================

    /// @brief Components of the vector
    float x, y, z;

    ////=======================================================================
    //// Constructor / Destructor
    ////=======================================================================


    /// @brief Default Constructor.
    SVector3();

    /// @brief Constructor with arguments.
    /// @param a_x float value which will initialize the x-component of vector.
    /// @param a_y float value which will initialize the y-component of vector.
    /// @param a_z float value which will initialize the z-component of vector.
    SVector3(float a_x, float a_y, float a_z = 0);

    ////=======================================================================
    //// Public Member functions
    ////=======================================================================


    /// @brief Returns the vector with normalization.
    /// @return Returns the vector with length = 1.0f.
    SVector3 Normalized();

    /// @brief Normalizes the vector.
    void Normalize();

    /// @brief Calculates the length (magnitude) of vector.
    /// @return Returns the length of the vector.
    float Length() const;

    ////=======================================================================
    //// Operator overload
    ////=======================================================================

    /// @brief Assigns a vector.
    /// @param a_vector1 Vector which will be assigned.
    inline void operator=(const SVector3& a_vector1);

    /// @brief Adds a vector.
    /// @param a_vector1 Vector which will be added.
    inline void operator+=(const SVector3& a_vector1);

    /// @brief Subtracts a vector.
    /// @param a_vector1 Vector which will be subtracted.
    inline void operator-=(const SVector3& a_vector1);

    /// @brief Multiplies a vector.
    /// @param a_vector1 Vector which will be multiplied.
    inline void operator*=(const SVector3& a_vector1);

    /// @brief Adds a scalar.
    /// @param a_scalar Scalar which will be multiplied.
    void operator*=(const float a_scalar);

    ////=======================================================================
    //// Static Functions
    ////=======================================================================

    /// @brief Calculates the dot product of two vectors.
    /// @param a_vector1 Requires a normalized Vector.
    /// @param a_vector2 Requires a normalized Vector.
    /// @return Returns a float value which ranges from -1.0f to 1.0f depending on the vector direction.
    static float Dot(const SVector3& a_vector1, const SVector3& a_vector2);

    static SVector3 Cross(const SVector3& a_vector1, const SVector3& a_vector2);

    /// @brief Normalizes a vector. The length will be set to 1.0f.
    /// @param a_vector1 A vector as reference.
    static void Normalize(SVector3& a_vector1);

    /// @brief Generates a normalized vector from another vector.
    /// @param a_vector1 A vector as reference.
    /// @return Returns a normalized vector.
    static SVector3 Normalized(const SVector3& a_vector1);

    /// @brief Calculates the distance between two vectors.
    /// @param a_vector1 A vector as reference.
    /// @param a_vector2 A vector as reference.
    /// @return Returns the distance between the two passed vectors.
    static float Distance(const SVector3& a_vector1, const SVector3& a_vector2);

    ////=======================================================================
    //// Static Members
    ////=======================================================================
    static SVector3 Zero();
    static SVector3 One();
    static SVector3 Right();
    static SVector3 Left();
    static SVector3 Up();
    static SVector3 Down();
    static SVector3 Forward();
    static SVector3 Backward();
};

////=======================================================================
//// Global Operator overload
////=======================================================================
inline void SVector3::operator=(const SVector3& a_vector1)
{
    this->x = a_vector1.x;
    this->y = a_vector1.y;
    this->z = a_vector1.z;
}
inline void SVector3::operator+=(const SVector3& a_vector1)
{
    this->x += a_vector1.x;
    this->y += a_vector1.y;
    this->z += a_vector1.z;
}
inline void SVector3::operator-=(const SVector3& a_vector1)
{
    this->x -= a_vector1.x;
    this->y -= a_vector1.y;
    this->z -= a_vector1.z;
}
inline void SVector3::operator*=(const SVector3& a_vector1)
{
    this->x *= a_vector1.x;
    this->y *= a_vector1.y;
    this->z *= a_vector1.z;
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
    SVector3 tmp;
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
    SVector3 tmp;
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
    SVector3 tmp;
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
    SVector3 tmp;
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
    SVector3 tmp;
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
    SVector3 tmp;
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