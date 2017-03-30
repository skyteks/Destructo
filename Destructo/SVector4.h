#pragma once
#include <math.h>


struct SVector4
{
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

	/// @brief Copy Constructor.
	/// @param a_vector1 Vector which will initialize the vector.
	SVector4(const SVector4& a_vector1);

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
	/// @param a_vector1 Vector which will be assigned.
	inline void operator=(const SVector4& a_vector1);

	/// @brief Adds a vector.
	/// @param a_vector1 Vector which will be added.
	inline void operator+=(const SVector4& a_vector1);

	/// @brief Subtracts a vector.
	/// @param a_vector1 Vector which will be subtracted.
	inline void operator-=(const SVector4& a_vector1);

	/// @brief Multiplies a vector.
	/// @param a_vector1 Vector which will be multiplied.
	inline void operator*=(const SVector4& a_vector1);

	/// @brief Adds a scalar.
	/// @param a_scalar Scalar which will be multiplied.
	void operator*=(const float a_scalar);

	////=======================================================================
	//// Public Member variables
	////=======================================================================

	/// @brief Components of the vector
	float x, y, z, w;

	////=======================================================================
	//// Static Functions
	////=======================================================================

	/// @brief Calculates the dot product of two vectors.
	/// @param a_vector1 Requires a normalized Vector.
	/// @param a_vector2 Requires a normalized Vector.
	/// @return Returns a float value which ranges from -1.0f to 1.0f depending on the vector direction.
	static float Dot(const SVector4& a_vector1, const SVector4& a_vector2);

	/// @brief Normalizes a vector. The length will be set to 1.0f.
	/// @param a_vector1 A vector as reference.
	static void Normalize(SVector4& a_vector1);

	/// @brief Generates a normalized vector from another vector.
	/// @param a_vector1 A vector as reference.
	/// @return Returns a normalized vector.
	static SVector4 Normalized(const SVector4& a_vector1);

	/// @brief Calculates the distance between two vectors.
	/// @param a_vector1 A vector as reference.
	/// @param a_vector2 A vector as reference.
	/// @return Returns the distance between the two passed vectors.
	static float Distance(const SVector4& a_vector1, const SVector4& a_vector2);

	////=======================================================================
	//// Static Members
	////=======================================================================

	/// @brief Static Unit Vectors
	static SVector4 zero;
	static SVector4 one;

	/// @brief Static floating value required for calculating equalization from vectors.
	static float epsilon;

};


////=======================================================================
//// Global Operator overload
////=======================================================================
inline void SVector4::operator=(const SVector4 & a_vector1)
{
	this->x = a_vector1.x;
	this->y = a_vector1.y;
	this->z = a_vector1.z;
	this->w = a_vector1.w;
}
inline void SVector4::operator+=(const SVector4 & a_vector1)
{
	this->x += a_vector1.x;
	this->y += a_vector1.y;
	this->z += a_vector1.z;
	this->w += a_vector1.w;
}
inline void SVector4::operator-=(const SVector4 & a_vector1)
{
	this->x -= a_vector1.x;
	this->y -= a_vector1.y;
	this->z -= a_vector1.z;
	this->w -= a_vector1.w;
}
inline void SVector4::operator*=(const SVector4 & a_vector1)
{
	this->x *= a_vector1.x;
	this->y *= a_vector1.y;
	this->z *= a_vector1.z;
	this->w *= a_vector1.w;
}
inline void SVector4::operator*=(const float a_scalar)
{
	this->x *= a_scalar;
	this->y *= a_scalar;
	this->z *= a_scalar;
	this->w *= a_scalar;
}


/// @brief Adds two vectors.
/// @param a_vector1 A vector as reference.
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
/// @param a_vector1 A vector as reference.
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
/// @param a_vector1 A vector as reference.
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
/// @param a_vector1 A vector as reference.
/// @param a_scalar A scalar which will be multiplied with the vector.
/// @return Returns a new sized vector.
inline SVector4 operator*(const SVector4& a_vector1, const float a_scalar)
{
	SVector4 tmp;
	tmp.x = a_vector1.x * a_scalar;
	tmp.y = a_vector1.y * a_scalar;
	tmp.z = a_vector1.z * a_scalar;
	tmp.w = a_vector1.w * a_scalar;
	return tmp;
}

/// @brief Scales a vector.
/// @param a_scalar A scalar which will be multiplied with the vector.
/// @param a_vector1 A vector as reference.
/// @return Returns a new sized vector.
inline SVector4 operator*(const float a_scalar, const SVector4& a_vector1)
{
	SVector4 tmp;
	tmp.x = a_vector1.x * a_scalar;
	tmp.y = a_vector1.y * a_scalar;
	tmp.z = a_vector1.z * a_scalar;
	tmp.w = a_vector1.w * a_scalar;
	return tmp;
}

/// @brief Divides a vector.
/// @param a_vector1 A vector as reference.
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
/// @param a_vector1 A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns true if they are equal, else false.
inline bool operator==(const SVector4& a_vector1, const SVector4& a_vector2)
{
	return (a_vector1.x - a_vector2.x < SVector4::epsilon) &&
		(a_vector1.y - a_vector2.y < SVector4::epsilon) &&
		(a_vector1.z - a_vector2.z < SVector4::epsilon) &&
		(a_vector1.w - a_vector2.w < SVector4::epsilon);
}

/// @brief Checks for non-equalisation of two vectors.
/// @param a_vector1 A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns true if they are not equal, else false.
inline bool operator!=(const SVector4& a_vector1, const SVector4& a_vector2)
{
	return !(a_vector1 == a_vector2);
}