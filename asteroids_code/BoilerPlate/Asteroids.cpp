#include "Asteroids.hpp"
//OpenGL include
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Asteroids::Asteroids()
{
	origin = Vector2(100.0f, 150.0f);
	asteroid_state = BIG;
	angle_degree = 25.0f;
	auto_rotate = 0.0f;
	asteroids_points.push_back(Vector2(0.0f, 35.0f));
	asteroids_points.push_back(Vector2(0.0f, 10.0f));
	asteroids_points.push_back(Vector2(-15.0f, 0.0f));
	asteroids_points.push_back(Vector2(-25.0f, 0.0f));
	asteroids_points.push_back(Vector2(-15.0f, -15.0f));
	asteroids_points.push_back(Vector2(0.0f, -25.0f));
	asteroids_points.push_back(Vector2(15.0f, -15.0f));
	asteroids_points.push_back(Vector2(25.0f, -5.0f));
	asteroids_points.push_back(Vector2(25.0f, 15.0f));
	asteroids_points.push_back(Vector2(10.0f, 30.0f));
	asteroids_points_state = asteroids_points;
}

Asteroids::Asteroids(Vector2& st_position, float st_angle)
{
	origin = st_position;
	angle_degree = st_angle;
	auto_rotate = 0.0f;
	asteroids_points.push_back(Vector2(0.0f, 35.0f));
	asteroids_points.push_back(Vector2(0.0f, 10.0f));
	asteroids_points.push_back(Vector2(-15.0f, 0.0f));
	asteroids_points.push_back(Vector2(-25.0f, 0.0f));
	asteroids_points.push_back(Vector2(-15.0f, -15.0f));
	asteroids_points.push_back(Vector2(0.0f, -25.0f));
	asteroids_points.push_back(Vector2(15.0f, -15.0f));
	asteroids_points.push_back(Vector2(25.0f, -5.0f));
	asteroids_points.push_back(Vector2(25.0f, 15.0f));
	asteroids_points.push_back(Vector2(10.0f, 30.0f));
	asteroids_points_state = asteroids_points;
}

void Asteroids::Render()
{
	glLoadIdentity();
	float real_angle = angle_degree + auto_rotate;
	glTranslatef(origin.x, origin.y, 0.0f);
	glRotatef(real_angle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < asteroids_points.size(); x++)
	{
		glVertex2f(asteroids_points[x].x, asteroids_points[x].y);
	}
	glEnd();
}

void Asteroids::Move()
{
	float angle_radian = math_master.DegToRad(angle_degree);
	origin += Vector2(-asteroid_speed*sin(angle_radian), asteroid_speed*cos(angle_radian));
}

void Asteroids::Update(const int w_width, const int w_height)
{
	Move();
	auto_rotate += asteroid_rotation;
	if (auto_rotate > 360)
	{
		auto_rotate -= 360;
	}
	if (origin.x >= w_width / 2)
	{
		origin.x += -w_width;
	}
	if (origin.x <= -w_width / 2)
	{
		origin.x += w_width;
	}
	if (origin.y >= w_height / 2)
	{
		origin.y += -w_height;
	}
	if (origin.y <= -w_height / 2)
	{
		origin.y += w_height;
	}
	if (asteroid_state == BIG)
	{
		asteroids_points = asteroids_points_state;
	}
	if (asteroid_state == MEDIUM)
	{
		for (int x = 0; x < asteroids_points.size(); x++)
		{
			asteroids_points[x] = 0.5f * asteroids_points_state[x];
		}
	}
	if (asteroid_state == SMALL)
	{
		for (int x = 0; x < asteroids_points.size(); x++)
		{
			asteroids_points[x] = 0.25f * asteroids_points_state[x];
		}
	}
}

void Asteroids::ChangeSize()
{
	if(asteroid_state == SMALL)
	{
		asteroid_state = BIG;
		return;
	} 
	if (asteroid_state == MEDIUM)
	{
		asteroid_state = SMALL;
	}
	if (asteroid_state == BIG)
	{
		asteroid_state = MEDIUM;
	}
}