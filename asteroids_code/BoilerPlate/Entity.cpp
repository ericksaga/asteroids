#include "Entity.hpp"
//OpenGL include
#include <GL/glew.h>
#include <SDL_opengl.h>

Entity::Entity()
{
	m_origin = Vector2(0.0f, 0.0f);
	m_angle_degree = 0.0f;
	m_debugging = false;
}

void Entity::Warp(const int w_width, const int w_height)
{
	if (m_origin.x >= w_width / 2)
	{
		m_origin.x += -w_width;
	}
	if (m_origin.x <= -w_width / 2)
	{
		m_origin.x += w_width;
	}
	if (m_origin.y >= w_height / 2)
	{
		m_origin.y += -w_height;
	}
	if (m_origin.y <= -w_height / 2)
	{
		m_origin.y += w_height;
	}
}

void Entity::MoveForward()
{
	float LC_angle_radian = m_math_master.DegreeToRadian(m_angle_degree);
	m_origin += Vector2(-SPEED * sin(LC_angle_radian), SPEED * cos(LC_angle_radian));
}

void Entity::Update(const int w_width, const int w_height, const float delta_time)
{
	m_math_master.AngleNormalizeDegree(m_angle_degree);
	Warp(w_width, w_height);
}

void Entity::Render()
{

}

void Entity::RenderCircle()
{
	float LC_2pi = 2 * PI;
	float LC_actual_angle = LC_2pi / LINE_AMOUNT;
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < LINE_AMOUNT; x++)
	{
		glVertex2f(
			m_radius * cos(LC_actual_angle * x), 
			m_radius * sin(LC_actual_angle * x)
		);
	}
	glEnd();
}

void Entity::ActivateDebugMode()
{
	if (m_debugging)
	{
		m_debugging = false;
	}
	else
	{
		m_debugging = true;
	}
}

Vector2 Entity::GetOrigin()
{
	return m_origin;
}

float Entity::GetEntityRadius()
{
	return m_radius;
}
void Entity::ChangeDebuggingState(bool state)
{
	m_debugging = state;
}
bool Entity::DebuggingState()
{
	return m_debugging;
}

float Entity::GetEntityAngle()
{
	return m_angle_degree;
}