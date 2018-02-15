#pragma once

const float pi = 3.14159265359f;

class MathUtilities {

public:
	int FlToInt(float target);
	int FlToLowEvenInt(float target);
	int FlToHighEvenInt(float target);
	template<class type>
	type Max(type a, type b);
	template<class type>
	type Max(type a, type b, type c);
	template<class type>
	type Max(type a, type b, type c, type d);
	template<class type>
	type Min(type a, type b);
	template<class type>
	type Min(type a, type b, type c);
	template<class type>
	type Min(type a, type b, type c, type d);
	template<class type>
	type Clamp(type a, type b, type c);
	float DegToRad(float target);
	float RadToDeg(float target);
	float ADistanceDeg(float a, float b);
	float ADistanceRad(float a, float b);
	bool IsPow2(int target);
	float Interpolate(float start, float end, float target);

};