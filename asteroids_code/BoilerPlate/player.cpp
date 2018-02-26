// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "Player.hpp"
#include "Color.h"


void Player::Render()
{
	//if the player is dead it doesn't get rendered
	if (!dead)
	{
		glLoadIdentity();
		glTranslatef(origin.x, origin.y, 0.0);
		glRotatef(angle_degree, 0.0, 0.0, 1.0);
		glColor3f(1.0f, 1.0f, 1.0f);
		Ship_Render();
		//render the thruster when moving
		if (thruster_on)
		{
			Thruster_Render();
			thruster_on = false;
		}
		//render the circle in debuggoing mode
		if (debugging)
		{
			RenderCircle();
		}
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

void Player::Update(const int w_width, const int w_height, const float delta_time)
{	
	origin += delta_time * speed;
	speed -= (1.0f / mass)*speed;
	
	Entity::Update(w_width, w_height, delta_time);
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
	math_master.AngleNormalizeDegree(angle_degree);
}

void Player::RotateRight()
{
	angle_degree -= ROTATION_ANGLE;
	math_master.AngleNormalizeDegree(angle_degree);
}

Player::Player()
{
	origin = Vector2(0.0, 0.0);
	speed = Vector2(0.0, 0.0);
	angle_degree = 0.0;
	mass = 10.0;
	radius = 35.0f;
	dead = false;
	speed = Vector2(0.0, 0.0);
	figure_points.push_back(Vector2(0.0, 30.0));
	figure_points.push_back(Vector2(-7.0, 20.0));
	figure_points.push_back(Vector2(-10.0, 0.0));
	figure_points.push_back(Vector2(-25.0, -10.0));
	figure_points.push_back(Vector2(-30.0, -25.0));
	figure_points.push_back(Vector2(-25.0, -25.0));
	figure_points.push_back(Vector2(-10.0, -20.0));
	figure_points.push_back(Vector2(-5.0, -10.0));
	figure_points.push_back(Vector2(-2.5, -25.0));
	figure_points.push_back(Vector2(2.5, -25.0));
	figure_points.push_back(Vector2(5.0, -10.0));
	figure_points.push_back(Vector2(10.0, -20.0));
	figure_points.push_back(Vector2(25.0, -25.0));
	figure_points.push_back(Vector2(30.0, -25.0));
	figure_points.push_back(Vector2(25.0, -10.0));
	figure_points.push_back(Vector2(10.0, 0.0));
	figure_points.push_back(Vector2(7.0, 20.0));
	thruster_points.push_back(Vector2(-2.5, -25.0));
	thruster_points.push_back(Vector2(0.0, -35.0));
	thruster_points.push_back(Vector2(2.5, -25.0));
}