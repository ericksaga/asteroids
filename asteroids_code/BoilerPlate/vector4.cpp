#include "Vector4.hpp"

Vector4::Vector4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
	length = 0;
}

Vector4::Vector4(float axis_val)
{
	x = axis_val;
	y = axis_val;
	z = axis_val;
	w = axis_val;
	length = Length();
}

Vector4::Vector4(float x_axis, float y_axis, float z_axis, float w_axis)
{
	x = x_axis;
	y = y_axis;
	z = z_axis;
	w = w_axis;
	length = Length();
}

float Vector4::Length()
{
	return sqrt(x * x + y * y + z * z + w * w);
}

float Vector4::SquaredLength()
{
	return x * x + y * y + z * z + w * w;
}

float Vector4::Normalize()
{
	length = Length();
	float scale = 1.0f / length;
	x = x * scale;
	y = y * scale;
	z = z * scale;
	w = w * scale;

	return length;
}

Vector4 Vector4::operator+(const Vector4& rhs)
{
	return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

Vector4 Vector4::operator-(const Vector4&rhs)
{
	return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

Vector4 Vector4::operator*(const Vector4&rhs)
{
	return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

Vector4 Vector4::operator/(const Vector4& rhs)
{ 
	if (rhs.x == 0 || rhs.y == 0 || rhs.z == 0 || rhs.w == 0)
	{
		throw "Division by 0 is not defined";
	}

	return Vector4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
}

bool Vector4::operator==(const Vector4& rhs)
{
	return (x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (w == rhs.w);
}

bool Vector4::operator!=(const Vector4& rhs)
{
	return (x != rhs.x) || (y != rhs.y) || (z != rhs.z) || (w != rhs.w);
}

Vector4& Vector4::operator=(const Vector4& rhs)
{
	if (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w)
	{
		return *this;
	}

	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;
	return *this;
}

Vector4& Vector4::operator+=(const Vector4& rhs)
{
	x = rhs.x + x;
	y = rhs.y + y;
	z = rhs.z + z;
	w = rhs.w + w;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& rhs)
{
	x = x - rhs.x;
	y = y - rhs.y;
	z = z - rhs.z;
	w = w - rhs.w;
	return *this;
}

Vector4& Vector4::operator*=(const Vector4& rhs)
{
	x = x * rhs.x;
	y = y * rhs.y;
	z = z * rhs.z;
	w = w * rhs.w;
	return *this;
}

Vector4& Vector4::operator/=(const Vector4& rhs)
{
	if (rhs.x == 0 || rhs.y == 0 || rhs.z == 0 || rhs.w == 0)
	{
		throw "Division by 0 is not defined";
	}
	x = x / rhs.x;
	y = y / rhs.y;
	z = z / rhs.z;
	w = w / rhs.w;
	return *this;
}

Vector4 operator*(float esc_fact, const Vector4& vect)
{
	return Vector4(esc_fact * vect.x, esc_fact * vect.y, esc_fact * vect.z, esc_fact * vect.w);
}

Vector4 operator*(const Vector4& vect, float esc_fact)
{
	return Vector4(esc_fact * vect.x, esc_fact * vect.y, esc_fact * vect.z, esc_fact * vect.w);
}