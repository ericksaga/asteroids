#include "Asteroid.hpp"
//OpenGL include
#include <GL/glew.h>
#include <SDL_opengl.h>

Asteroid::Asteroid()
{
	m_origin = Vector2(100.0f, 150.0f);
	m_asteroid_state = BIG;
	m_angle_degree = 25.0f;
	m_auto_rotate = 0.0f;
	m_size_factor = 1.0f;
	m_radius = RADIUS;
	m_colide = false;
	m_close_to_ship = false;
	m_close_to_bullet = false;
	m_figure_points.push_back(Vector2(0.0f, 30.0f));
	m_figure_points.push_back(Vector2(0.0f, 10.0f));
	m_figure_points.push_back(Vector2(-15.0f, 0.0f));
	m_figure_points.push_back(Vector2(-25.0f, 0.0f));
	m_figure_points.push_back(Vector2(-15.0f, -15.0f));
	m_figure_points.push_back(Vector2(0.0f, -25.0f));
	m_figure_points.push_back(Vector2(15.0f, -15.0f));
	m_figure_points.push_back(Vector2(25.0f, -5.0f));
	m_figure_points.push_back(Vector2(25.0f, 20.0f));
	m_figure_points.push_back(Vector2(10.0f, 27.0f));
	m_asteroid_points_state = m_figure_points;
}
Asteroid::Asteroid(int size)
{
	m_origin = Vector2(100.0f, 150.0f);
	//size for small and medium asteroid, big asteroid on default constructor
	if (size == 2)
	{
		m_asteroid_state = SMALL;
		m_size_factor = (float)m_asteroid_state / 4.0f;
	}
	else if (size == 3)
	{
		m_asteroid_state = MEDIUM;
		m_size_factor = (float)m_asteroid_state / 4.0f;
	}
	m_angle_degree = 25.0f;
	m_auto_rotate = 0.0f;
	m_radius = RADIUS;
	m_colide = false;
	m_close_to_ship = false;
	m_close_to_bullet = false;
	m_figure_points.push_back(Vector2(0.0f, 30.0f));
	m_figure_points.push_back(Vector2(0.0f, 10.0f));
	m_figure_points.push_back(Vector2(-15.0f, 0.0f));
	m_figure_points.push_back(Vector2(-25.0f, 0.0f));
	m_figure_points.push_back(Vector2(-15.0f, -15.0f));
	m_figure_points.push_back(Vector2(0.0f, -25.0f));
	m_figure_points.push_back(Vector2(15.0f, -15.0f));
	m_figure_points.push_back(Vector2(25.0f, -5.0f));
	m_figure_points.push_back(Vector2(25.0f, 20.0f));
	m_figure_points.push_back(Vector2(10.0f, 27.0f));
	m_asteroid_points_state = m_figure_points;
}

void Asteroid::Render()
{
	glLoadIdentity();
	float LC_real_angle = m_angle_degree + m_auto_rotate;
	glTranslatef(m_origin.x, m_origin.y, 0.0f);
	glRotatef(LC_real_angle, 0.0f, 0.0f, 1.0f);
	glColor3f(0.9f, 0.9f, 0.9f);
	//red asteroid if coliding, only on the debugging mode
	if (m_colide)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	RenderAsteroid();
	//render the circle in debugging moode
	if (m_debugging)
	{
		RenderCircle();
	}
}

void Asteroid::RenderAsteroid()
{
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < m_figure_points.size(); x++)
	{
		glVertex2f(m_figure_points[x].x, m_figure_points[x].y);
	}
	glEnd();
}

void Asteroid::MoveForward(const float delta_time)
{
	//calculate speed depending on the size, smallest = fastest
	float LC_angle_radian = m_math_master.DegreeToRadian(m_angle_degree);
	float LC_speed_factor = 1/m_size_factor;
	float LC_speed_x = LC_speed_factor * ASTEROID_SPEED * -sin(LC_angle_radian);
	float LC_speed_y = LC_speed_factor * ASTEROID_SPEED * cos(LC_angle_radian);
	m_origin += delta_time * Vector2(LC_speed_x, LC_speed_y);
}

void Asteroid::Update(const int w_width, const int w_height, const float delta_time)
{
	MoveForward(delta_time);
	m_auto_rotate += ASTEROID_ROTATION;
	Entity::Update(w_width, w_height, delta_time);
	MeasureSizeFactor();
}

void Asteroid::MeasureSizeFactor()
{
	//change all the points and the radius depending the size of the asteroid
	if (m_asteroid_state == BIG)
	{
		m_radius = RADIUS;
		m_figure_points = m_asteroid_points_state;
	}
	if (m_asteroid_state == MEDIUM)
	{
		m_radius = RADIUS * m_size_factor;
		for (int x = 0; x < m_figure_points.size(); x++)
		{
			m_figure_points[x] = m_size_factor * m_asteroid_points_state[x];
		}
	}
	if (m_asteroid_state == SMALL)
	{
		m_radius = RADIUS * m_size_factor;
		for (int x = 0; x < m_figure_points.size(); x++)
		{
			m_figure_points[x] = m_size_factor * m_asteroid_points_state[x];
		}
	}
}

void Asteroid::ChangeSize()
{
	/*this is the changesize code, it have the small to big for the debugging mode, when you can change
	the asteroid size*/
	if(m_asteroid_state == SMALL)
	{
		m_asteroid_state = BIG;
		m_size_factor = (float)m_asteroid_state/4.0f;
	} 
	else if (m_asteroid_state == MEDIUM)
	{
		m_asteroid_state = SMALL;
		m_size_factor = (float)m_asteroid_state / 4.0f;
	}
	else if (m_asteroid_state == BIG)
	{
		m_asteroid_state = MEDIUM;
		m_size_factor = (float)m_asteroid_state / 4.0f;
	}
}

int Asteroid::GetSize()
{
	return m_asteroid_state;
}

void Asteroid::AssignOrientation(int random_number)
{
	m_angle_degree = (float) (random_number % 360);
}

void Asteroid::AssignPosition(int random_number_x, int random_number_y)
{
	/*assing the random position with the values, for it to be more random if the number is even the
	position is negative, and if it's odd it would be positive*/
	float LC_pos_x, LC_pos_y;
	LC_pos_x = (float)(random_number_x % MAX_SPAWN_POSITION + MIN_SPAWN_POSITION);
	LC_pos_y = (float)(random_number_y % MAX_SPAWN_POSITION + MIN_SPAWN_POSITION);
	if (random_number_x % 2 == 0)
	{
		LC_pos_x *= -1;
	}
	if (random_number_y % 2 == 1)
	{
		LC_pos_y *= -1;
	}
	m_origin = Vector2(LC_pos_x, LC_pos_y);
}

void Asteroid::AssignPosition(Vector2 position)
{
	m_origin = position;
}

void Asteroid::DebugLine(const Vector2 player)
{
	/* Draw a line between the player and the asteroid, the identity gets loaded because the asteroid is
	rotating every time and the line has to be fixed to the player, if it's depending on the asteroid it
	will be rotating*/
	glLoadIdentity();
	glBegin(GL_LINE_STRIP);
	glVertex2f(m_origin.x, m_origin.y);
	glVertex2f(player.x, player.y);
	glEnd();
}

bool Asteroid::Colide()
{
	return m_colide;
}

void Asteroid::AssignColide(bool state)
{
	m_colide = state;
}

bool Asteroid::CloseToShip()
{
	return m_close_to_ship;
}

void Asteroid::CheckShipDistance(bool state)
{
	m_close_to_ship = state;
}

bool Asteroid::CloseToBullet()
{
	return m_close_to_bullet;
}

void Asteroid::CheckBulletDistance(bool state)
{
	m_close_to_bullet = state;
}