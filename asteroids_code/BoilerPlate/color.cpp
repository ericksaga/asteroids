#include "color.h"

Color::Color()
{
	red = 0.0;
	blue = 0.0;
	green = 0.0;
	alpha = 0.0;
}
Color::Color(float r, float g, float b, float aph)
{
	red = r;
	green = g;
	blue = b;
	alpha = aph;
}