#pragma once
#include "GLIncludes.hpp"
#include <string>

class GLTextRenderer
{

public:
	GLTextRenderer();
	GLTextRenderer(TTF_Font*, SDL_Color);
	void TextRenderInit();
	void RenderText(std::string message, SDL_Color color, float x, float y, int size);
	unsigned int power_two_floor(unsigned int);


private:

	TTF_Font* font;
	SDL_Color color;

};