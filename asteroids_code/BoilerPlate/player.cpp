// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "player.hpp"
#include "color.h"

void player::move(const vector2& mov)
{
	origin += mov;
}

void player::render()
{
	
	glBegin(GL_LINE_LOOP);
	glVertex2f(50.0 + origin.x, 50.0 + origin.y);
	glVertex2f(50.0 + origin.x, -50.0 + origin.y);
	glVertex2f(-50.0 + origin.x, -50.0 + origin.y);
	glVertex2f(-50.0 + origin.x, 50.0 + origin.y);
	glEnd();
}

player::player()
{
	origin = vector2(0, 0);
}