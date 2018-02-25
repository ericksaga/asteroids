#pragma once
#include <cmath>
#include "mathUtilities.hpp"
struct Vector2 {
	
	//members
	float x;
	float y;
	float length;

	//constructor
	Vector2();
	Vector2(float, float);
	Vector2(float);

	//functions

	float Length();
	float SquaredLength();
	float Normalize();
	float GetAngle();
	float VectorialDistance(Vector2);
	//Overload
	Vector2 operator+(const Vector2&);
	Vector2 operator-(const Vector2&);
	Vector2 operator*(const Vector2&);
	Vector2 operator/(const Vector2&);
	bool operator==(const Vector2&);
	bool operator!=(const Vector2&);
	Vector2& operator=(const Vector2&);
	Vector2& operator+=(const Vector2&);
	Vector2& operator-=(const Vector2&);
	Vector2& operator*=(const Vector2&);
	Vector2& operator/=(const Vector2&);
	friend Vector2 operator*(float, const Vector2&);
	friend Vector2 operator*(const Vector2&, float);



};