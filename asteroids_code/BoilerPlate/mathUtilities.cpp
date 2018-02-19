#include "MathUtilities.hpp"

int MathUtilities::FloatToInt(float target)
{
	int acc = (int) target;
	if (target - acc >= 0.5)
	{
		acc++;
	}
	return acc;
}

int MathUtilities::FloatToLowEvenInt(float target)
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
int MathUtilities::FloatToHighEvenInt(float target)
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

float MathUtilities::DegreeToRadian(float target)
{
	return target * (PI / 180.0f);
}

float MathUtilities::RadianToDegree(float target)
{
	return target * (180.0f / PI);
}

float MathUtilities::AngularDistanceDegree(float a, float b)
{
	float result;
	result = a - b;
	if (result < 0)
	{
		result = 360 + result;
	}
	return result;
}

float MathUtilities::AngularDistanceRadian(float a, float b)
{
	float result;
	result = a - b;
	if (result < 0)
	{
		result = 2 * PI + result;
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

float MathUtilities::AngleNormalizeDegree(float target)
{
	if (target > 360)
	{
		return target - 360;
	}
	if (target < -360)
	{
		return target + 360;
	}
	return target;
}
float MathUtilities::AngleNormalizeRadian(float target)
{
	float Max_angle = 2 * PI;
	if (target > Max_angle)
	{
		return target - Max_angle;
	}
	if (target < -Max_angle)
	{
		return target + Max_angle;
	}
	return target;
}