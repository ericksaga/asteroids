#include "mathUtilities.hpp"

int mathUtilities::fltoint(float target)
{
	int acc = (int) target;
	if (target - acc >= 0.5)
	{
		acc++;
	}
	return acc;
}

int mathUtilities::fltolowevenint(float target)
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
int mathUtilities::fltohighevenint(float target)
{
	int acc = (int) target;
	if (acc % 2 != 0)
	{
		acc++;
	}
	return acc;
}

template<class type>
type mathUtilities::max(type a, type b)
{
	type acc = b;
	if (a > b)
	{
		acc = a;
	}
	return acc;
}

template<class type>
type mathUtilities::max(type a, type b, type c)
{
	type acc = max(a, b);
	acc = max(acc, c);
	return acc;
}

template<class type>
type mathUtilities::max(type a, type b, type c, type d)
{
	type acc = max(a, b, c);
	acc = max(acc, d);
	return acc;
}

template<class type>
type mathUtilities::min(type a, type b)
{
	type acc = b;
	if (a < b)
	{
		acc = a;
	}
	return acc;
}

template<class type>
type mathUtilities::min(type a, type b, type c)
{
	type acc = min(a, b);
	acc = min(acc, c);
	return acc;
}

template<class type>
type mathUtilities::min(type a, type b, type c, type d)
{
	type acc = min(a, b, c);
	acc = min(acc, d);
	return acc;
}

template<class type>
type mathUtilities::clamp(type r_min, type r_max, type target)
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

float mathUtilities::degtorad(float target)
{
	return target * (180 / pi);
}

float mathUtilities::radtodeg(float target)
{
	return target * (pi / 180);
}

float mathUtilities::adistancedeg(float a, float b)
{
	float result;
	result = a - b;
	if (result < 0)
	{
		result = 360 + result;
	}
	return result;
}

float mathUtilities::adistancerad(float a, float b)
{
	float result;
	result = a - b;
	if (result < 0)
	{
		result = 2 * pi + result;
	}
	return result;
}

bool mathUtilities::ispow2(int target)
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

float mathUtilities::interpolate(float start, float end, float target)
{
	return target * (end - start) + start;
}	