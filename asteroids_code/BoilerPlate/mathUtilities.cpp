#include "MathUtilities.hpp"

int MathUtilities::FlToInt(float target)
{
	int acc = (int) target;
	if (target - acc >= 0.5)
	{
		acc++;
	}
	return acc;
}

int MathUtilities::FlToLowEvenInt(float target)
{
	int acc = (int) target;
	if (acc % 2 != 0)
	{
		if (target - acc < 0.5)
		{
			acc--;
		}
		else
		{
			acc++;
		}
	}
	return acc;
}
int MathUtilities::FlToHighEvenInt(float target)
{
	int acc = (int) target;
	if (acc % 2 != 0)
	{
		acc++;
	}
	return acc;
}

template<class type>
type MathUtilities::Max(type a, type b)
{
	type acc = b;
	if (a > b)
	{
		acc = a;
	}
	return acc;
}

template<class type>
type MathUtilities::Max(type a, type b, type c)
{
	type acc = Max(a, b);
	acc = Max(acc, c);
	return acc;
}

template<class type>
type MathUtilities::Max(type a, type b, type c, type d)
{
	type acc = Max(a, b, c);
	acc = Max(acc, d);
	return acc;
}

template<class type>
type MathUtilities::Min(type a, type b)
{
	type acc = b;
	if (a < b)
	{
		acc = a;
	}
	return acc;
}

template<class type>
type MathUtilities::Min(type a, type b, type c)
{
	type acc = Min(a, b);
	acc = Min(acc, c);
	return acc;
}

template<class type>
type MathUtilities::Min(type a, type b, type c, type d)
{
	type acc = Min(a, b, c);
	acc = Min(acc, d);
	return acc;
}

template<class type>
type MathUtilities::Clamp(type r_min, type r_max, type target)
{
	if (target < min)
	{
		target = min;
	}
	else if (target > max)
	{
		target = max;
	}
	return target;
}

float MathUtilities::DegToRad(float target)
{
	return target * (180 / pi);
}

float MathUtilities::RadToDeg(float target)
{
	return target * (pi / 180);
}

float MathUtilities::ADistanceDeg(float a, float b)
{
	float result;
	result = a - b;
	if (result < 0)
	{
		result = 360 + result;
	}
	return result;
}

float MathUtilities::ADistanceRad(float a, float b)
{
	float result;
	result = a - b;
	if (result < 0)
	{
		result = 2 * pi + result;
	}
	return result;
}

bool MathUtilities::IsPow2(int target)
{
	int acc = 1;
	bool result = false;
	for (int x = 0; acc < target; x++)
	{
		acc *= 2;
		if (acc == target)
		{
			result = true;
		}
	}
	return result;
}

float MathUtilities::Interpolate(float start, float end, float target)
{
	return target * (end - start) + start;
}	