#include "vector2.hpp"

#include <cmath>

vector2::vector2()
{
	x = 0.0f;
	y = 0.0f;
	length = 0.0f;
}

vector2::vector2(float cord_x, float cord_y)
{
	x = cord_x;
	y = cord_y;
	length = Length();
}

vector2::vector2(float value)
{
	x = value;
	y = value;
	length = Length();
}

//functions

float vector2::Length()
{
	return sqrt(x * x + y * y);
}

float vector2::squaredlength()
{
	return x * x + y * y;
}

float vector2::normalize()
{
	length = Length();
	float scale = 1.0f / length;
	x *= scale;
	y *= scale;
	return length;
}

//Overload

vector2 vector2::operator+(const vector2& val)
{
	return vector2(x + val.x, y + val.y);
}

vector2 vector2::operator-(const vector2& val)
{
	return vector2(x - val.x, y - val.y);
}

vector2 vector2::operator*(const vector2& val)
{
	return vector2(x * val.x, y * val.y);
}

vector2 vector2::operator/(const vector2& val)
{
	if (val.x == 0 || val.y == 0)
	{
		throw "Division by zero is not defined!";
	}


	return vector2(x / val.x, y / val.y);
	
}

bool vector2::operator==(const vector2& val)
{
	return (val.x == x) && (val.y == y);
}
bool vector2::operator!=(const vector2& val)
{
	return (val.x != x) || (val.y != y);
}

vector2& vector2::operator=(const vector2& val)
{
	if (*this == val)
	{
		return *this;
	}
	x = val.x;
	y = val.y;
	return *this;
}

vector2& vector2::operator+=(const vector2& val)
{
	x = val.x + x;
	y = val.y + y;
	return *this;
}

vector2& vector2::operator-=(const vector2& val)
{
	x = x - val.x;
	y = y - val.y;
	return *this;
}

vector2& vector2::operator*=(const vector2& val)
{
	x = x * val.x;
	y = y * val.y;
	return *this;
}

vector2& vector2::operator/=(const vector2& val)
{
	if (val.x == 0 || val.y == 0)
	{
		throw "Division by zero is not defined!";
	}
	x = x / val.x;
	y = y / val.y;
	 
	return *this;
}

vector2 operator*(float mult, const vector2& vect) 
{
	return vector2(mult * vect.x, mult * vect.y);
}

vector2 operator*(const vector2& vect, float mult)
{
	return vector2(mult * vect.x, mult * vect.y);
}