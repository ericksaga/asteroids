#pragma once
#include <cmath>
struct Vector3 {

	//members
	float x;
	float y;
	float z;
	float length;

	//constructor
	Vector3();
	Vector3(float, float, float);
	Vector3(float);

	//functions

	float Length();
	float SquaredLength();
	float Normalize();

	//Overload

	Vector3 operator+(const Vector3&);
	Vector3 operator-(const Vector3&);
	Vector3 operator*(const Vector3&);
	Vector3 operator/(const Vector3&);
	bool operator==(const Vector3&);
	bool operator!=(const Vector3&);
	Vector3& operator=(const Vector3&);
	Vector3& operator+=(const Vector3&);
	Vector3& operator-=(const Vector3&);
	Vector3& operator*=(const Vector3&);
	Vector3& operator/=(const Vector3&);
	friend Vector3 operator*(float, const Vector3&);
	friend Vector3 operator*(const Vector3&, float);
	
};