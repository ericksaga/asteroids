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
	glRotatef(angle_degree, 0.0, 0.0, 1.0);
	Ship_Render();
	if (thruster_on)
	{
		Thruster_Render();
		thruster_on = false;
	}

}

void Player::Ship_Render()
{
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < ship_points.size();x++)
	{
		glVertex2f(ship_points[x].x, ship_points[x].y);
	}
	glEnd();
}

void Player::Thruster_Render()
{
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < thruster_points.size(); x++)
	{
		glVertex2f(thruster_points[x].x, thruster_points[x].y);
	}
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
	float angle_radians = conv.DegToRad(angle_degree);
	origin += Vector2(-move_speed * sin(angle_radians), move_speed * cos(angle_radians));
	//origin += Vector2(0.0, move_speed);
	thruster_on = true;
}

void Player::RotateLeft()
{
	angle_degree += rotation_angle;
	if (angle_degree >= 360)
	{
		angle_degree -= 360;
	}
}

void Player::RotateRight()
{
	angle_degree -= rotation_angle;
	if (angle_degree <= -360)
	{
		angle_degree += 360;
	}
}

Player::Player()
{
	origin = Vector2(0.0, 0.0);
	angle_degree = 0.0;
	mass = 0.0;
	ship_points.push_back(Vector2(0.0, 30.0));
	ship_points.push_back(Vector2(-10.0, 0.0));
	ship_points.push_back(Vector2(-25.0, -10.0));
	ship_points.push_back(Vector2(-35.0, -25.0));
	ship_points.push_back(Vector2(-25.0, -25.0));
	ship_points.push_back(Vector2(-10.0, -20.0));
	ship_points.push_back(Vector2(-5.0, -10.0));
	ship_points.push_back(Vector2(-2.5, -25.0));
	ship_points.push_back(Vector2(2.5, -25.0));
	ship_points.push_back(Vector2(5.0, -10.0));
	ship_points.push_back(Vector2(10.0, -20.0));
	ship_points.push_back(Vector2(25.0, -25.0));
	ship_points.push_back(Vector2(35.0, -25.0));
	ship_points.push_back(Vector2(25.0, -10.0));
	ship_points.push_back(Vector2(10.0, 0.0));
	thruster_points.push_back(Vector2(-2.5, -25.0));
	thruster_points.push_back(Vector2(0.0, -35.0));
	thruster_points.push_back(Vector2(2.5, -25.0));
}