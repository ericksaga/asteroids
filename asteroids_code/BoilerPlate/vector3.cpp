#include "vector3.hpp"
#include <cmath>

vector3::vector3()
{
	x = 0;
	y = 0;
	z = 0;
	length = 0;
}

vector3::vector3(float value)
{
	x = value;
	y = value;
	z = value;
	length = Length();
}

vector3::vector3(float cord_x, float cord_y, float cord_z)
{
	x = cord_x;
	y = cord_y;
	z = cord_z;
	length = Length();
}

float vector3::Length()
{
	return sqrt(x * x + y * y + z * z);
}

float vector3::squaredlength()
{
	return x * x + y * y + z * z;
}

float vector3::normalize()
{
	length = Length();
	float scale = 1.0f / length;
	x = x * scale;
	y = y * scale;
	z = z * scale;

	return length;
}

vector3 vector3::operator+(const vector3& val)
{
	return vector3(x + val.x, y + val.y, z + val.z);
}

vector3 vector3::operator-(const vector3& val)
{
	return vector3(x - val.x, y - val.y, z - val.z);
}

vector3 vector3::operator*(const vector3& val)
{
	return vector3(x * val.x, y * val.y, z * val.z);
}

vector3 vector3::operator/(const vector3& val)
{
	if (val.x == 0 || val.y == 0 || val.z == 0)
	{
		throw "Division by 0 is not defined";
	}

	return vector3(x / val.x, y / val.y, z / val.z);
}

bool vector3::operator==(const vector3& val)
{
	return (x == val.x) && (y == val.y) && (z == val.z);
}

bool vector3::operator!=(const vector3& val)
{
	return (x != val.x) || (y != val.y) || (z != val.z);
}

vector3& vector3::operator=(const vector3& val)
{
	if (x == val.x && y == val.y && z == val.z)
	{
		return *this;
	}

	x = val.x;
	y = val.y;
	z = val.z;
	return *this;
}

vector3& vector3::operator+=(const vector3& val)
{
	x = val.x + x;
	y = val.y + y;
	z = val.z + z;
	return *this;
}

vector3& vector3::operator-=(const vector3& val)
{
	x = x - val.x;
	y = y - val.y;
	z = z - val.z;
	return *this;
}

vector3& vector3::operator*=(const vector3& val)
{
	x = x * val.x;
	y = y * val.y;
	z = z * val.z;
	return *this;
}

vector3& vector3::operator/=(const vector3& val)
{
	if (val.x == 0 || val.y == 0 || val.z == 0)
	{
		throw "Division by 0 is not defined";
	}
	x = x / val.x;
	y = y / val.y;
	z = z / val.z;
	return *this;
}

vector3 operator*(float mult, const vector3& vect)
{
	return vector3(mult * vect.x, mult * vect.y, mult * vect.z);
}

vector3 operator*(const vector3& vect, float mult)
{
	return vector3(mult * vect.x, mult * vect.y, mult * vect.z);
}