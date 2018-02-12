// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "Player.hpp"
#include "Color.h"


void Player::Render()
{
	//put a thrusting figure (like a fire) at the back of the spaceship
	glLoadIdentity();
	glTranslatef(origin.x, origin.y, 0.0);
	Ship_Render();
}

void Player::Ship_Render()
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0, 30.0);
	glVertex2f(-10.0, 0.0);
	glVertex2f(-25.0, -10.0);
	glVertex2f(-35.0, -25.0);
	glVertex2f(-25.0, -25.0);
	glVertex2f(-10.0, -20.0);
	glVertex2f(-5.0, -10.0);
	glVertex2f(-2.5, -25.0);
	glVertex2f(2.5, -25.0);
	glVertex2f(5.0, -10.0);
	glVertex2f(10.0, -20.0);
	glVertex2f(25.0, -25.0);
	glVertex2f(35.0, -25.0);
	glVertex2f(25.0, -10.0);
	glVertex2f(10.0, 0.0);
	glEnd();
}

void Player::Update(const int w_width, const int w_height)
{
	//glRotatef(-angle_degree, 0.0, 0.0, 1.0);
	if (origin.x >= w_width/2)
	{
		origin.x += -w_width;
	}
	if (origin.x <= -w_width/2)
	{
		origin.x += w_width;
	}
	if (origin.y >= w_height/2)
	{
		origin.y += -w_height;
	}
	if (origin.y <= -w_height/2)
	{
		origin.y += w_height;
	}
	//glRotatef(angle_degree, 0.0, 0.0, 1.0);
}

void Player::MoveForward()
{
	//origin += vector2(move_speed * cos(angle_degree / 57.3), move_speed * sin(angle_degree / 57.3));
	origin += Vector2(0.0, move_speed);
}

void Player::RotateLeft()
{
	/*glRotatef(rotation_angle, 0.0, 0.0, 1.0);
	angle_degree += 4;*/
}

void Player::RotateRight()
{
	/*glRotatef(-rotation_angle, 0.0, 0.0, 1.0);
	angle_degree -= rotation_angle;*/
}

Player::Player()
{
	origin = Vector2(0.0, 0.0);
	angle_degree = 90.0;
}