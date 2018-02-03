#pragma once

struct vector2 {
	
	//members
	float x;
	float y;
	float length;

	//constructor
	vector2();
	vector2(float, float);
	vector2(float);

	//functions

	float Length();
	float squaredlength();
	float normalize();
	
	//Overload

	vector2 operator+(const vector2&);
	vector2 operator-(const vector2&);
	vector2 operator*(const vector2&);
	vector2 operator/(const vector2&);
	bool operator==(const vector2&);
	bool operator!=(const vector2&);
	vector2& operator=(const vector2&);
	vector2& operator+=(const vector2&);
	vector2& operator-=(const vector2&);
	vector2& operator*=(const vector2&);
	vector2& operator/=(const vector2&);
	friend vector2 operator*(float, const vector2&);
	friend vector2 operator*(const vector2&, float);



};