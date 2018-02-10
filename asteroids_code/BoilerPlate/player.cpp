// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "player.hpp"
#include "color.h"


void player::render()
{
	//put a thrusting figure (like a fire) at the back of the spaceship
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0, 50.0);
	glVertex2f(-30.0, -20.0);
	glVertex2f(30.0, -20.0);
	glEnd();
}

void player::update()
{
	glRotatef(-angle, 0.0, 0.0, 1.0);
	if (origin.x >= 568)
	{
		glTranslatef(0.0, -1136.0, 0.0);
		origin.x += -1136.0;
	}
	if (origin.x <= -568)
	{
		glTranslatef(0.0, 1136.0, 0.0);
		origin.x += 1136.0;
	}
	if (origin.y >= 320)
	{
		glTranslatef(640, 0.0, 0.0);
		origin.y += -640;
	}
	if (origin.y <= -320)
	{
		glTranslatef(-640.0, 0.0, 0.0);
		origin.y += 640.0;
	}
	glRotatef(angle, 0.0, 0.0, 1.0);
}

void player::moveforward()
{
	glTranslatef(0.0, 2.5, 0.0);
	origin += vector2(2.5 * cos(angle / 57.3), 2.5 * sin(angle / 57.3));

}

void player::rotateleft()
{
	glRotatef(4.0, 0.0, 0.0, 1.0);
	angle += 4;
}

void player::rotateright()
{
	glRotatef(-4.0, 0.0, 0.0, 1.0);
	angle -= 4;
}

player::player()
{
	origin = vector2(0, 0);
	angle = 90;
}