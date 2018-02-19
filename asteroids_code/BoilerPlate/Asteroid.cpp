#include "Asteroid.hpp"
//OpenGL include
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Asteroid::Asteroid()
{
	origin = Vector2(100.0f, 150.0f);
	asteroid_state = BIG;
	angle_degree = 25.0f;
	auto_rotate = 0.0f;
	figure_points.push_back(Vector2(0.0f, 35.0f));
	figure_points.push_back(Vector2(0.0f, 10.0f));
	figure_points.push_back(Vector2(-15.0f, 0.0f));
	figure_points.push_back(Vector2(-25.0f, 0.0f));
	figure_points.push_back(Vector2(-15.0f, -15.0f));
	figure_points.push_back(Vector2(0.0f, -25.0f));
	figure_points.push_back(Vector2(15.0f, -15.0f));
	figure_points.push_back(Vector2(25.0f, -5.0f));
	figure_points.push_back(Vector2(25.0f, 15.0f));
	figure_points.push_back(Vector2(10.0f, 30.0f));
	asteroid_points_state = figure_points;
}

Asteroid::Asteroid(Vector2& st_position, float st_angle)
{
	origin = st_position;
	angle_degree = st_angle;
	auto_rotate = 0.0f;
	asteroid_state = BIG;
	figure_points.push_back(Vector2(0.0f, 35.0f));
	figure_points.push_back(Vector2(0.0f, 10.0f));
	figure_points.push_back(Vector2(-15.0f, 0.0f));
	figure_points.push_back(Vector2(-25.0f, 0.0f));
	figure_points.push_back(Vector2(-15.0f, -15.0f));
	figure_points.push_back(Vector2(0.0f, -25.0f));
	figure_points.push_back(Vector2(15.0f, -15.0f));
	figure_points.push_back(Vector2(25.0f, -5.0f));
	figure_points.push_back(Vector2(25.0f, 15.0f));
	figure_points.push_back(Vector2(10.0f, 30.0f));
	asteroid_points_state = figure_points;
}

void Asteroid::Render()
{
	glLoadIdentity();
	float real_angle = angle_degree + auto_rotate;
	glTranslatef(origin.x, origin.y, 0.0f);
	glRotatef(real_angle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < figure_points.size(); x++)
	{
		glVertex2f(figure_points[x].x, figure_points[x].y);
	}
	glEnd();
}

void Asteroid::MoveForward()
{
	float angle_radian = math_master.DegreeToRadian(angle_degree);
	origin += Vector2(-ASTEROID_SPEED * sin(angle_radian), ASTEROID_SPEED * cos(angle_radian));
}

void Asteroid::Update(const int w_width, const int w_height)
{
	MoveForward();
	auto_rotate += ASTEROID_ROTATION;
	if (auto_rotate > 360)
	{
		auto_rotate -= 360;
	}
	Warp(w_width, w_height);

	if (asteroid_state == BIG)
	{
		figure_points = asteroid_points_state;
	}
	if (asteroid_state == MEDIUM)
	{
		for (int x = 0; x < figure_points.size(); x++)
		{
			figure_points[x] = 0.75f * asteroid_points_state[x];
		}
	}
	if (asteroid_state == SMALL)
	{
		for (int x = 0; x < figure_points.size(); x++)
		{
			figure_points[x] = 0.5f * asteroid_points_state[x];
		}
	}
}

void Asteroid::ChangeSizeForTest()
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

int Asteroid::GetSize()
{
	return asteroid_state;
}