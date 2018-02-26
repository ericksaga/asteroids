#include "Bullet.hpp"
//OpenGL include
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Bullet::Bullet()
{
	m_origin = Vector2(0.0f, 0.0f);
	m_angle_degree = 0.0f;
	m_radius = 7.5f;
	m_screen_time = 0;
	m_figure_points.push_back(Vector2(5.0f, 5.0f));
	m_figure_points.push_back(Vector2(-5.0f, 5.0f));
	m_figure_points.push_back(Vector2(-5.0f, -5.0f));
	m_figure_points.push_back(Vector2(5.0f, -5.0f));
}

Bullet::Bullet(float angle, Entity* ship)
{
	m_origin = ship->GetOrigin();
	m_angle_degree = angle;
	m_origin.x += ship->GetEntityRadius() * -sin(m_math_master.DegreeToRadian(m_angle_degree));
	m_origin.y += ship->GetEntityRadius() * cos(m_math_master.DegreeToRadian(m_angle_degree));
	m_radius = 7.5f;
	m_screen_time = 0;
	m_figure_points.push_back(Vector2(5.0f, 5.0f));
	m_figure_points.push_back(Vector2(-5.0f, 5.0f));
	m_figure_points.push_back(Vector2(-5.0f, -5.0f));
	m_figure_points.push_back(Vector2(5.0f, -5.0f));
}

void Bullet::MoveForward(const float delta_time)
{
	//calculate speed depending on the size, smallest = fastest
	float LC_angle_radian = m_math_master.DegreeToRadian(m_angle_degree);
	float LC_speed_x = BULLET_SPEED * -sin(LC_angle_radian);
	float LC_speed_y = BULLET_SPEED * cos(LC_angle_radian);
	m_origin += delta_time * Vector2(LC_speed_x, LC_speed_y);
}

void Bullet::Update(const int w_width, const int w_height, const float delta_time)
{
	MoveForward(delta_time);
	Entity::Update(w_width, w_height, delta_time);
	m_screen_time++;
}

void Bullet::Render()
{
	glLoadIdentity();
	glTranslatef(m_origin.x, m_origin.y, 0.0f);
	glRotatef(m_angle_degree, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	BulletRender();
	if (m_debugging)
	{
		RenderCircle();
	}
}

void Bullet::BulletRender()
{
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < m_figure_points.size(); x++)
	{
		glVertex2f(m_figure_points[x].x, m_figure_points[x].y);
	}
	glEnd();
}

int Bullet::GetScreenTime()
{
	return m_screen_time;
}