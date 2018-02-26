#pragma once


const float PI = 3.14159265359f;

struct MathUtilities {

	int FloatToInt(float target);
	int FloatToLowEvenInt(float target);
	int FloatToHighEvenInt(float target);
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
	float DegreeToRadian(float target);
	float RadianToDegree(float target);
	float AngularDistanceDegree(float a, float b);
	float AngularDistanceRadian(float a, float b);
	bool IsPow2(int target);
	float Interpolate(float start, float end, float target);
	float AngleNormalizeDegree(float);
	float AngleNormalizeRadian(float);
};