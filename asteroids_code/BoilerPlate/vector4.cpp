#include "vector4.hpp"

vector4::vector4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
	length = 0;
}

vector4::vector4(float value)
{
	x = value;
	y = value;
	z = value;
	w = value;
	length = Length();
}

vector4::vector4(float cord_x, float cord_y, float cord_z, float cord_w)
{
	x = cord_x;
	y = cord_y;
	z = cord_z;
	w = cord_w;
	length = Length();
}

float vector4::Length()
{
	return sqrt(x * x + y * y + z * z + w * w);
}

float vector4::squaredlength()
{
	return x * x + y * y + z * z + w * w;
}

float vector4::normalize()
{
	length = Length();
	float scale = 1.0f / length;
	x = x * scale;
	y = y * scale;
	z = z * scale;
	w = w * scale;

	return length;
}

vector4 vector4::operator+(const vector4& val)
{
	return vector4(x + val.x, y + val.y, z + val.z, w + val.w);
}

vector4 vector4::operator-(const vector4& val)
{
	return vector4(x - val.x, y - val.y, z - val.z, w - val.w);
}

vector4 vector4::operator*(const vector4& val)
{
	return vector4(x * val.x, y * val.y, z * val.z, w * val.w);
}

vector4 vector4::operator/(const vector4& val)
{
	if (val.x == 0 || val.y == 0 || val.z == 0 || val.w == 0)
	{
		throw "Division by 0 is not defined";
	}

	return vector4(x / val.x, y / val.y, z / val.z, w / val.w);
}

bool vector4::operator==(const vector4& val)
{
	return (x == val.x) && (y == val.y) && (z == val.z) && (w == val.w);
}

bool vector4::operator!=(const vector4& val)
{
	return (x != val.x) || (y != val.y) || (z != val.z) || (w != val.w);
}

vector4& vector4::operator=(const vector4& val)
{
	if (x == val.x && y == val.y && z == val.z && w == val.w)
	{
		return *this;
	}

	x = val.x;
	y = val.y;
	z = val.z;
	w = val.w;
	return *this;
}

vector4& vector4::operator+=(const vector4& val)
{
	x = val.x + x;
	y = val.y + y;
	z = val.z + z;
	w = val.w + w;
	return *this;
}

vector4& vector4::operator-=(const vector4& val)
{
	x = x - val.x;
	y = y - val.y;
	z = z - val.z;
	w = w - val.w;
	return *this;
}

vector4& vector4::operator*=(const vector4& val)
{
	x = x * val.x;
	y = y * val.y;
	z = z * val.z;
	w = w * val.w;
	return *this;
}

vector4& vector4::operator/=(const vector4& val)
{
	if (val.x == 0 || val.y == 0 || val.z == 0 || val.w == 0)
	{
		throw "Division by 0 is not defined";
	}
	x = x / val.x;
	y = y / val.y;
	z = z / val.z;
	w = w / val.w;
	return *this;
}

vector4 operator*(float mult, const vector4& vect)
{
	return vector4(mult * vect.x, mult * vect.y, mult * vect.z, mult * vect.w);
}

vector4 operator*(const vector4& vect, float mult)
{
	return vector4(mult * vect.x, mult * vect.y, mult * vect.z, mult * vect.w);
}