// OpenGL includes
#include <GL/glew.h>
#include <SDL_opengl.h>
#include "Player.hpp"
#include "Color.h"


void Player::Render()
{
	//if the player is dead it doesn't get rendered
	if (!dead)
	{
		glLoadIdentity();
		glTranslatef(m_origin.x, m_origin.y, 0.0);
		glRotatef(m_angle_degree, 0.0, 0.0, 1.0);
		glColor3f(1.0f, 1.0f, 1.0f);
		Ship_Render();
		//render the thruster when moving
		if (m_thruster_on)
		{
			Thruster_Render();
			m_thruster_on = false;
		}
		//render the circle in debuggoing mode
		if (m_debugging)
		{
			RenderCircle();
		}
	}
}

void Player::Ship_Render()
{
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < m_figure_points.size(); x++)
	{
		glVertex2f(m_figure_points[x].x, m_figure_points[x].y);
	}
	glEnd();
}

void Player::Thruster_Render()
{
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < m_thruster_points.size(); x++)
	{
		glVertex2f(m_thruster_points[x].x, m_thruster_points[x].y);
	}
	glEnd();
}

void Player::Update(const int w_width, const int w_height, const float delta_time)
{	
	m_origin += delta_time * m_speed;
	m_speed -= (1.0f / m_mass)*m_speed;
	
	Entity::Update(w_width, w_height, delta_time);
}

void Player::MoveForward()
{
	float LC_angle_radians = m_math_master.DegreeToRadian(m_angle_degree);
	m_speed += Vector2(-MOVE_SPEED * sin(LC_angle_radians), MOVE_SPEED * cos(LC_angle_radians));
	m_thruster_on = true;
}

void Player::RotateLeft()
{
	m_angle_degree += ROTATION_ANGLE;
	m_math_master.AngleNormalizeDegree(m_angle_degree);
}

void Player::RotateRight()
{
	m_angle_degree -= ROTATION_ANGLE;
	m_math_master.AngleNormalizeDegree(m_angle_degree);
}

std::vector<Vector2> Player::GetShipPoints()
{
	return m_figure_points;
}

Player::Player()
{
	m_origin = Vector2(0.0, 0.0);
	m_speed = Vector2(0.0, 0.0);
	m_angle_degree = 0.0;
	m_mass = 10.0;
	m_radius = 35.0f;
	dead = false;
	m_speed = Vector2(0.0, 0.0);
	m_figure_points.push_back(Vector2(0.0, 30.0));
	m_figure_points.push_back(Vector2(-7.0, 20.0));
	m_figure_points.push_back(Vector2(-10.0, 0.0));
	m_figure_points.push_back(Vector2(-25.0, -10.0));
	m_figure_points.push_back(Vector2(-30.0, -25.0));
	m_figure_points.push_back(Vector2(-25.0, -25.0));
	m_figure_points.push_back(Vector2(-10.0, -20.0));
	m_figure_points.push_back(Vector2(-5.0, -10.0));
	m_figure_points.push_back(Vector2(-2.5, -25.0));
	m_figure_points.push_back(Vector2(2.5, -25.0));
	m_figure_points.push_back(Vector2(5.0, -10.0));
	m_figure_points.push_back(Vector2(10.0, -20.0));
	m_figure_points.push_back(Vector2(25.0, -25.0));
	m_figure_points.push_back(Vector2(30.0, -25.0));
	m_figure_points.push_back(Vector2(25.0, -10.0));
	m_figure_points.push_back(Vector2(10.0, 0.0));
	m_figure_points.push_back(Vector2(7.0, 20.0));
	m_thruster_points.push_back(Vector2(-2.5, -25.0));
	m_thruster_points.push_back(Vector2(0.0, -35.0));
	m_thruster_points.push_back(Vector2(2.5, -25.0));
}