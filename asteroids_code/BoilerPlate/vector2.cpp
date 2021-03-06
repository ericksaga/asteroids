#include "Vector2.hpp"


Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
	length = 0.0f;
}

Vector2::Vector2(float x_axis, float y_axis)
{
	x = x_axis;
	y = y_axis;
	length = Length();
}

Vector2::Vector2(float axis_val)
{
	x = axis_val;
	y = axis_val;
	length = Length();
}

//functions

float Vector2::Length()
{
	return sqrt(x * x + y * y);
}

float Vector2::SquaredLength()
{
	return x * x + y * y;
}

float Vector2::Normalize()
{
	length = Length();
	float LC_scale = 1.0f / length;
	x *= LC_scale;
	y *= LC_scale;
	return length;
}

float Vector2::GetAngle()
{
	MathUtilities LC_math_master;
	float LC_angle_degree = 90.0f;
	if (x != 0)
	{
		LC_angle_degree = LC_math_master.RadianToDegree(atan(y / x));
	}
	LC_math_master.AngleNormalizeDegree(LC_angle_degree);
	if (x < 0.0f && y >= 0.0f)
	{
		LC_angle_degree -= 180.0f;
	}
	else if (x < 0.0f && y < 0.0f)
	{
		LC_angle_degree += 180.0f;
	}
	return LC_angle_degree;
}

float Vector2::VectorialDistance(Vector2 point)
{
	float LC_x_val = x - point.x;
	float LC_y_val = y - point.y;
	return sqrt(LC_x_val*LC_x_val + LC_y_val*LC_y_val);
}

//Overload

Vector2 Vector2::operator+(const Vector2& rhs)
{
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs)
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator*(const Vector2& rhs)
{
	return Vector2(x * rhs.x, y * rhs.y);
}

Vector2 Vector2::operator/(const Vector2& rhs)
{
	if ( rhs.x == 0 || rhs.y == 0)
	{
		throw "Division by zero is not defined!";
	}


	return Vector2(x / rhs.x, y / rhs.y);
	
}

bool Vector2::operator==(const Vector2& rhs)
{
	return (rhs.x == x) && (rhs.y == y);
}
bool Vector2::operator!=(const Vector2& rhs)
{
	return (rhs.x != x) || (rhs.y != y);
}

Vector2& Vector2::operator=(const Vector2& rhs)
{
	if (*this == rhs)
	{
		return *this;
	}
	x = rhs.x;
	y = rhs.y;
	return *this;
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	x = rhs.x + x;
	y = rhs.y + y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	x = x - rhs.x;
	y = y - rhs.y;
	return *this;
}

Vector2& Vector2::operator*=(const Vector2& rhs)
{
	x = x * rhs.x;
	y = y * rhs.y;
	return *this;
}

Vector2& Vector2::operator/=(const Vector2& rhs)
{
	if ( rhs.x == 0 || rhs.y == 0)
	{
		throw "Division by zero is not defined!";
	}
	x = x / rhs.x;
	y = y / rhs.y;
	 
	return *this;
}

Vector2 operator*(float esc_fact, const Vector2& vect) 
{
	return Vector2(esc_fact * vect.x, esc_fact * vect.y);
}

Vector2 operator*(const Vector2& vect, float esc_fact)
{
	return Vector2(esc_fact * vect.x, esc_fact * vect.y);
}