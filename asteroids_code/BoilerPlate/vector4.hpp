#pragma once

#include <cmath>
struct Vector4 {

	//members
	float x;
	float y;
	float z;
	float w;
	float length;

	//constructor
	Vector4();
	Vector4(float, float, float, float);
	Vector4(float);

	//functions

	float Length();
	float SquaredLength();
	float Normalize();

	//Overload

	Vector4 operator+(const Vector4&);
	Vector4 operator-(const Vector4&);
	Vector4 operator*(const Vector4&);
	Vector4 operator/(const Vector4&);
	bool operator==(const Vector4&);
	bool operator!=(const Vector4&);
	Vector4& operator=(const Vector4&);
	Vector4& operator+=(const Vector4&);
	Vector4& operator-=(const Vector4&);
	Vector4& operator*=(const Vector4&);
	Vector4& operator/=(const Vector4&);
	friend Vector4 operator*(float, const Vector4&);
	friend Vector4 operator*(const Vector4&, float);

};