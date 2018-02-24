// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "Player.hpp"
#include "Color.h"


void Player::Render()
{
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
	for (int x = 0; x < figure_points.size(); x++)
	{
		glVertex2f(figure_points[x].x, figure_points[x].y);
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
	origin += speed;
	ApplyFriction();
	Entity::Update(w_width, w_height);
}

void Player::MoveForward()
{
	float LC_angle_radians = math_master.DegreeToRadian(angle_degree);
	speed += Vector2(-MOVE_SPEED * sin(LC_angle_radians), MOVE_SPEED * cos(LC_angle_radians));
	thruster_on = true;
}

void Player::RotateLeft()
{
	angle_degree += ROTATION_ANGLE;
}

void Player::RotateRight()
{
	angle_degree -= ROTATION_ANGLE;
}

Player::Player()
{
	origin = Vector2(0.0, 0.0);
	speed = Vector2(0.0, 0.0);
	angle_degree = 0.0;
	mass = 10.0;
	speed = Vector2(0.0, 0.0);
	figure_points.push_back(Vector2(0.0, 30.0));
	figure_points.push_back(Vector2(-10.0, 0.0));
	figure_points.push_back(Vector2(-25.0, -10.0));
	figure_points.push_back(Vector2(-35.0, -25.0));
	figure_points.push_back(Vector2(-25.0, -25.0));
	figure_points.push_back(Vector2(-10.0, -20.0));
	figure_points.push_back(Vector2(-5.0, -10.0));
	figure_points.push_back(Vector2(-2.5, -25.0));
	figure_points.push_back(Vector2(2.5, -25.0));
	figure_points.push_back(Vector2(5.0, -10.0));
	figure_points.push_back(Vector2(10.0, -20.0));
	figure_points.push_back(Vector2(25.0, -25.0));
	figure_points.push_back(Vector2(35.0, -25.0));
	figure_points.push_back(Vector2(25.0, -10.0));
	figure_points.push_back(Vector2(10.0, 0.0));
	thruster_points.push_back(Vector2(-2.5, -25.0));
	thruster_points.push_back(Vector2(0.0, -35.0));
	thruster_points.push_back(Vector2(2.5, -25.0));
}

void Player::ApplyFriction()
{
	speed = (9 / mass)*speed;
	/*float LC_speed_angle = math_master.DegreeToRadian(speed.GetAngle());
	Vector2 LC_mspeed = Vector2(0.5f * cos(LC_speed_angle), 0.5f * sin(LC_speed_angle));
	if (speed.x > 0.0f)
	{
		speed.x -= LC_mspeed.x;
		if (speed.x < 0.0f)
		{
			speed.x = 0.0f;
		}
	}
	else if (speed.x < 0.0f)
	{
		speed.x -= LC_mspeed.x;
		if (speed.x > 0.0f)
		{
			speed.x = 0.0f;
		}
	}
	if (speed.y > 0.0f)
	{
		speed.y -= LC_mspeed.y;
		if (speed.y < 0.0f)
		{
			speed.y = 0.0f;
		}
	}
	else if (speed.y < 0.0f)
	{
		speed.y -= LC_mspeed.y;
		if (speed.y > 0.0f)
		{
			speed.y = 0.0f;
		}
	}*/
}