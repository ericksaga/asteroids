#pragma once
#include "GLIncludes.hpp"
#include <string>

class TextRenderer
{

public:
	TextRenderer();
	TextRenderer(SDL_Color);
	void RenderText(std::string message, SDL_Color color, float x, float y, int size);
	unsigned int power_two_floor(unsigned int);
	bool InitFont();

private:

	TTF_Font* font;
	SDL_Color color;

};