#include "palet.h"

color palet::redscreen()
{
	color acc(1.0, 0.0, 0.0, 1.0);
	return acc;
}

color palet::bluescreen()
{
	color acc(0.0, 0.0, 1.0, 1.0);
	return acc;
}

color palet::greenscreen()
{
	color acc(0.0, 1.0, 0.0, 1.0);
	return acc;
}

color palet::darkbluescreen()
{
	color acc(0.0, 0.0, 0.54, 1.0);
	return acc;
}