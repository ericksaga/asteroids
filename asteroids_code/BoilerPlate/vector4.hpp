#pragma once

#include <cmath>
struct vector4 {

	//members
	float x;
	float y;
	float z;
	float w;
	float length;

	//constructor
	vector4();
	vector4(float, float, float, float);
	vector4(float);

	//functions

	float Length();
	float squaredlength();
	float normalize();

	//Overload

	vector4 operator+(const vector4&);
	vector4 operator-(const vector4&);
	vector4 operator*(const vector4&);
	vector4 operator/(const vector4&);
	bool operator==(const vector4&);
	bool operator!=(const vector4&);
	vector4& operator=(const vector4&);
	vector4& operator+=(const vector4&);
	vector4& operator-=(const vector4&);
	vector4& operator*=(const vector4&);
	vector4& operator/=(const vector4&);
	friend vector4 operator*(float, const vector4&);
	friend vector4 operator*(const vector4&, float);

};