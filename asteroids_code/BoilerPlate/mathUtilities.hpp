#pragma once

const float pi = 3.14159265359;

class mathUtilities {

public:
	int fltoint(float target);
	int fltolowevenint(float target);
	int fltohighevenint(float target);
	template<class type>
	type max(type a, type b);
	template<class type>
	type max(type a, type b, type c);
	template<class type>
	type max(type a, type b, type c, type d);
	template<class type>
	type min(type a, type b);
	template<class type>
	type min(type a, type b, type c);
	template<class type>
	type min(type a, type b, type c, type d);
	template<class type>
	type clamp(type a, type b, type c);
	float degtorad(float target);
	float radtodeg(float target);
	float adistancedeg(float a, float b);
	float adistancerad(float a, float b);
	bool ispow2(int target);
	float interpolate(float start, float end, float target);

};