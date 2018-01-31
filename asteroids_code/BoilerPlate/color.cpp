#include "color.h"

color::color()
{
	red = 0.0;
	blue = 0.0;
	green = 0.0;
	alpha = 0.0;
}
color::color(float r, float g, float b, float aph)
{
	red = r;
	green = g;
	blue = b;
	alpha = aph;
}

void color::setred(float target)
{
	red = target;
}

void color::setgreen(float target)
{
	green = target;
}

void color::setblue(float target)
{
	blue = target;
}

void color::setalpha(float target)
{
	alpha = target;
}

void color::setall(float r, float g, float b, float aph)
{
	red = r;
	green = g;
	blue = b;
	alpha = aph;
}

float color::getred()
{
	return red;
}

float color::getgreen()
{
	return green;
}

float color::getblue()
{
	return blue;
}

float color::getalpha()
{
	return alpha;
}