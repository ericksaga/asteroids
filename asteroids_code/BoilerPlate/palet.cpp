#include "Palet.h"

Color Palet::RedScreen()
{
	Color acc(1.0f, 0.0f, 0.0f, 1.0f);
	return acc;
}

Color Palet::BlueScreen()
{
	Color acc(0.0f, 0.0f, 1.0f, 1.0f);
	return acc;
}

Color Palet::GreenScreen()
{
	Color acc(0.0f, 1.0f, 0.0f, 1.0f);
	return acc;
}

Color Palet::DarkBlueScreen()
{
	Color acc(0.0f, 0.0f, 0.54f, 1.0f);
	return acc;
}