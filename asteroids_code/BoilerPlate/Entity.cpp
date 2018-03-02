#include "Entity.hpp"
#include "GLIncludes.hpp"

Entity::Entity()
{
	m_origin = Vector2(0.0f, 0.0f);
	m_angle_degree = 0.0f;
	m_debugging = false;
}

void Entity::UpdateWarp(const int screen_width, const int screen_height)
{
	m_width = screen_width;
	m_height = screen_height;
}

void Entity::Warp()
{
	float LC_half_width = (float)m_width / 2.0f;
	float LC_half_height = (float)m_height / 2.0f;
	if (m_origin.x >= LC_half_width)
	{
		m_origin.x += -m_width;
	}
	if (m_origin.x <= -LC_half_width)
	{
		m_origin.x += m_width;
	}
	if (m_origin.y >= LC_half_height)
	{
		m_origin.y += -m_height;
	}
	if (m_origin.y <= -LC_half_height)
	{
		m_origin.y += m_height;
	}
}

void Entity::MoveForward()
{
	float LC_angle_radian = m_math_master.DegreeToRadian(m_angle_degree);
	m_origin += Vector2(-SPEED * sin(LC_angle_radian), SPEED * cos(LC_angle_radian));
}

void Entity::Update(const float delta_time)
{
	m_math_master.AngleNormalizeDegree(m_angle_degree);
	Warp();
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