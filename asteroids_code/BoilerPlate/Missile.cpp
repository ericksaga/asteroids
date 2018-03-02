#include "Missile.hpp"
#include "GLIncludes.hpp"

Missile::Missile()
{
	m_origin = Vector2(0.0f, 0.0f);
	m_angle_degree = 0.0f;
	m_radius = 8;
	m_screen_time = 0;
	m_figure_points.push_back(Vector2(0.0f, 8.0f));
	m_figure_points.push_back(Vector2(-2.0f, 6.0f));
	m_figure_points.push_back(Vector2(-2.0f, 0.0f));
	m_figure_points.push_back(Vector2(-6.0f, -6.0f));
	m_figure_points.push_back(Vector2(-2.0f, -6.0f));
	m_figure_points.push_back(Vector2(-2.0f, 0.0f));
	m_figure_points.push_back(Vector2(-2.0f, -6.0f));
	m_figure_points.push_back(Vector2(2.0f, -6.0f));
	m_figure_points.push_back(Vector2(6.0f, -6.0f));
	m_figure_points.push_back(Vector2(2.0f, 0.0f));
	m_figure_points.push_back(Vector2(2.0f, -6.0f));
	m_figure_points.push_back(Vector2(2.0f, 0.0f));
	m_figure_points.push_back(Vector2(2.0f, 6.0f));
}

Missile::Missile(float angle, Entity* ship)
{
	m_origin = ship->GetOrigin();
	m_angle_degree = angle;
	m_origin.x += ship->GetEntityRadius() * -sin(m_math_master.DegreeToRadian(m_angle_degree));
	m_origin.y += ship->GetEntityRadius() * cos(m_math_master.DegreeToRadian(m_angle_degree));
	m_radius = 8;
	m_screen_time = 0;
	m_figure_points.push_back(Vector2(0.0f, 8.0f));
	m_figure_points.push_back(Vector2(-2.0f, 6.0f));
	m_figure_points.push_back(Vector2(-2.0f, 0.0f));
	m_figure_points.push_back(Vector2(-6.0f, -6.0f));
	m_figure_points.push_back(Vector2(-2.0f, -6.0f));
	m_figure_points.push_back(Vector2(-2.0f, 0.0f));
	m_figure_points.push_back(Vector2(-2.0f, -6.0f));
	m_figure_points.push_back(Vector2(2.0f, -6.0f));
	m_figure_points.push_back(Vector2(6.0f, -6.0f));
	m_figure_points.push_back(Vector2(2.0f, 0.0f));
	m_figure_points.push_back(Vector2(2.0f, -6.0f));
	m_figure_points.push_back(Vector2(2.0f, 0.0f));
	m_figure_points.push_back(Vector2(2.0f, 6.0f));
}

void Missile::MoveForward(const float delta_time)
{
	//calculate speed depending on the size, smallest = fastest
	float LC_angle_radian = m_math_master.DegreeToRadian(m_angle_degree);
	float LC_speed_x = MISSILE_SPEED * -sin(LC_angle_radian);
	float LC_speed_y = MISSILE_SPEED * cos(LC_angle_radian);
	m_origin += delta_time * Vector2(LC_speed_x, LC_speed_y);
}

void Missile::Update(const float delta_time)
{
	MoveForward(delta_time);
	Entity::Update(delta_time);
	m_screen_time++;
}

void Missile::Render()
{
	glLoadIdentity();
	glTranslatef(m_origin.x, m_origin.y, 0.0f);
	glRotatef(m_angle_degree, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	MissileRender();
	if (m_debugging)
	{
		RenderCircle();
	}
}

void Missile::MissileRender()
{
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < m_figure_points.size(); x++)
	{
		glVertex2f(m_figure_points[x].x, m_figure_points[x].y);
	}
	glEnd();
}

int Missile::GetScreenTime()
{
	return m_screen_time;
}

std::vector<Vector2> Missile::GetMissilePoints()
{
	return m_figure_points;
}