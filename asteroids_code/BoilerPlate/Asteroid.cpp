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
	size_factor = 1.0f;
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
	float LC_real_angle = angle_degree + auto_rotate;
	glTranslatef(origin.x, origin.y, 0.0f);
	glRotatef(LC_real_angle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < figure_points.size(); x++)
	{
		glVertex2f(figure_points[x].x, figure_points[x].y);
	}
	glEnd();
}

void Asteroid::MoveForward()
{
	float LC_angle_radian = math_master.DegreeToRadian(angle_degree);
	float LC_speed_factor = 1/size_factor;
	float LC_speed_x = LC_speed_factor * ASTEROID_SPEED * -sin(LC_angle_radian);
	float LC_speed_y = LC_speed_factor * ASTEROID_SPEED * cos(LC_angle_radian);
	origin += Vector2(LC_speed_x, LC_speed_y);
}

void Asteroid::Update(const int w_width, const int w_height)
{
	MoveForward();
	auto_rotate += ASTEROID_ROTATION;
	Entity::Update(w_width, w_height);

	if (asteroid_state == BIG)
	{
		figure_points = asteroid_points_state;
	}
	if (asteroid_state == MEDIUM)
	{
		for (int x = 0; x < figure_points.size(); x++)
		{
			figure_points[x] = size_factor * asteroid_points_state[x];
		}
	}
	if (asteroid_state == SMALL)
	{
		for (int x = 0; x < figure_points.size(); x++)
		{
			figure_points[x] = size_factor * asteroid_points_state[x];
		}
	}
}

void Asteroid::ChangeSizeForTest()
{
	if(asteroid_state == SMALL)
	{
		size_factor = 1.0f;
		asteroid_state = BIG;
	} 
	else if (asteroid_state == MEDIUM)
	{
		size_factor = 0.5f;
		asteroid_state = SMALL;
	}
	else if (asteroid_state == BIG)
	{
		size_factor = 0.75f;
		asteroid_state = MEDIUM;
	}
}

int Asteroid::GetSize()
{
	return asteroid_state;
}

void Asteroid::AssignOrientation(int random_number)
{
	angle_degree = (float) (random_number % 360);
}

void Asteroid::AssignPosition(int random_number_x, int random_number_y)
{
	float LC_pos_x, LC_pos_y;
	LC_pos_x = (float)(random_number_x % 201 + 100);
	LC_pos_y = (float)(random_number_y % 201 + 100);
	if (random_number_x % 2 == 0)
	{
		LC_pos_x *= -1;
	}
	if (random_number_y % 2 == 1)
	{
		LC_pos_y *= -1;
	}
	origin = Vector2(LC_pos_x, LC_pos_y);
}