#include "Vector3.hpp"

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
	length = 0;
}

Vector3::Vector3(float axis_val)
{
	x = axis_val;
	y = axis_val;
	z = axis_val;
	length = Length();
}

Vector3::Vector3(float x_axis, float y_axis, float z_axis)
{
	x = x_axis;
	y = y_axis;
	z = z_axis;
	length = Length();
}

float Vector3::Length()
{
	return sqrt(x * x + y * y + z * z);
}

float Vector3::SquaredLength()
{
	return x * x + y * y + z * z;
}

float Vector3::Normalize()
{
	length = Length();
	float scale = 1.0f / length;
	x = x * scale;
	y = y * scale;
	z = z * scale;

	return length;
}

Vector3 Vector3::operator+(const Vector3& rhs)
{
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3 Vector3::operator-(const Vector3& rhs)
{
	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3 Vector3::operator*(const Vector3& rhs)
{
	return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
}

Vector3 Vector3::operator/(const Vector3& rhs)
{
	if ( rhs.x == 0 || rhs.y == 0 || rhs.z == 0)
	{
		throw "Division by 0 is not defined";
	}

	return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
}

bool Vector3::operator==(const Vector3& rhs)
{
	return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}

bool Vector3::operator!=(const Vector3& rhs)
{
	return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
}

Vector3& Vector3::operator=(const Vector3& rhs)
{
	if (x == rhs.x && y == rhs.y && z == rhs.z)
	{
		return *this;
	}

	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
	x = rhs.x + x;
	y = rhs.y + y;
	z = rhs.z + z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
	x = x - rhs.x;
	y = y - rhs.y;
	z = z - rhs.z;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& rhs)
{
	x = x * rhs.x;
	y = y * rhs.y;
	z = z * rhs.z;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& rhs)
{
	if ( rhs.x == 0 || rhs.y == 0 || rhs.z == 0)
	{
		throw "Division by 0 is not defined";
	}
	x = x / rhs.x;
	y = y / rhs.y;
	z = z / rhs.z;
	return *this;
}

Vector3 operator*(float esc_fact, const Vector3& vect)
{
	return Vector3(esc_fact * vect.x, esc_fact * vect.y, esc_fact * vect.z);
}

Vector3 operator*(const Vector3& vect, float esc_fact)
{
	return Vector3(esc_fact * vect.x, esc_fact * vect.y, esc_fact * vect.z);
}