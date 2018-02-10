#pragma once
#include <cmath>
struct vector3 {

	//members
	float x;
	float y;
	float z;
	float length;

	//constructor
	vector3();
	vector3(float, float, float);
	vector3(float);

	//functions

	float Length();
	float squaredlength();
	float normalize();

	//Overload

	vector3 operator+(const vector3&);
	vector3 operator-(const vector3&);
	vector3 operator*(const vector3&);
	vector3 operator/(const vector3&);
	bool operator==(const vector3&);
	bool operator!=(const vector3&);
	vector3& operator=(const vector3&);
	vector3& operator+=(const vector3&);
	vector3& operator-=(const vector3&);
	vector3& operator*=(const vector3&);
	vector3& operator/=(const vector3&);
	friend vector3 operator*(float, const vector3&);
	friend vector3 operator*(const vector3&, float);
	
};