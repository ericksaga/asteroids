#include "Palet.h"

Color Palet::RedScreen()
{
	Color acc(1.0, 0.0, 0.0, 1.0);
	return acc;
}

Color Palet::BlueScreen()
{
	Color acc(0.0, 0.0, 1.0, 1.0);
	return acc;
}

Color Palet::GreenScreen()
{
	Color acc(0.0, 1.0, 0.0, 1.0);
	return acc;
}

Color Palet::DarkBlueScreen()
{
	Color acc(0.0, 0.0, 0.54, 1.0);
	return acc;
}