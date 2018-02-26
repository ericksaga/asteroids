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
	radius = 30.0f;
	colide = false;
	close_to_ship = false;
	close_to_bullet = false;
	figure_points.push_back(Vector2(0.0f, 30.0f));
	figure_points.push_back(Vector2(0.0f, 10.0f));
	figure_points.push_back(Vector2(-15.0f, 0.0f));
	figure_points.push_back(Vector2(-25.0f, 0.0f));
	figure_points.push_back(Vector2(-15.0f, -15.0f));
	figure_points.push_back(Vector2(0.0f, -25.0f));
	figure_points.push_back(Vector2(15.0f, -15.0f));
	figure_points.push_back(Vector2(25.0f, -5.0f));
	figure_points.push_back(Vector2(25.0f, 20.0f));
	figure_points.push_back(Vector2(10.0f, 27.0f));
	asteroid_points_state = figure_points;
}
Asteroid::Asteroid(int size)
{
	origin = Vector2(100.0f, 150.0f);
	//size for small and medium asteroid, big asteroid on default constructor
	if (size == 1)
	{
		asteroid_state = SMALL;
		size_factor = 0.5f;
	}
	else if (size == 2)
	{
		asteroid_state = MEDIUM;
		size_factor = 0.75f;
	}
	angle_degree = 25.0f;
	auto_rotate = 0.0f;
	radius = 30.0f;
	colide = false;
	close_to_ship = false;
	close_to_bullet = false;
	figure_points.push_back(Vector2(0.0f, 30.0f));
	figure_points.push_back(Vector2(0.0f, 10.0f));
	figure_points.push_back(Vector2(-15.0f, 0.0f));
	figure_points.push_back(Vector2(-25.0f, 0.0f));
	figure_points.push_back(Vector2(-15.0f, -15.0f));
	figure_points.push_back(Vector2(0.0f, -25.0f));
	figure_points.push_back(Vector2(15.0f, -15.0f));
	figure_points.push_back(Vector2(25.0f, -5.0f));
	figure_points.push_back(Vector2(25.0f, 20.0f));
	figure_points.push_back(Vector2(10.0f, 27.0f));
	asteroid_points_state = figure_points;
}

void Asteroid::Render()
{
	glLoadIdentity();
	float LC_real_angle = angle_degree + auto_rotate;
	glTranslatef(origin.x, origin.y, 0.0f);
	glRotatef(LC_real_angle, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	//red asteroid if coliding, only on the debugging mode
	if (colide)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	RenderAsteroid();
	//render the circle in debugging moode
	if (debugging)
	{
		RenderCircle();
	}
}

void Asteroid::RenderAsteroid()
{
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < figure_points.size(); x++)
	{
		glVertex2f(figure_points[x].x, figure_points[x].y);
	}
	glEnd();
}

void Asteroid::MoveForward(const float delta_time)
{
	//calculate speed depending on the size, smallest = fastest
	float LC_angle_radian = math_master.DegreeToRadian(angle_degree);
	float LC_speed_factor = 1/size_factor;
	float LC_speed_x = LC_speed_factor * ASTEROID_SPEED * -sin(LC_angle_radian);
	float LC_speed_y = LC_speed_factor * ASTEROID_SPEED * cos(LC_angle_radian);
	origin += delta_time * Vector2(LC_speed_x, LC_speed_y);
}

void Asteroid::Update(const int w_width, const int w_height, const float delta_time)
{
	MoveForward(delta_time);
	auto_rotate += ASTEROID_ROTATION;
	Entity::Update(w_width, w_height, delta_time);
	SizeRefactor();
}

void Asteroid::SizeRefactor()
{
	//change all the points and the radius depending the size of the asteroid
	if (asteroid_state == BIG)
	{
		radius = 30.0f;
		figure_points = asteroid_points_state;
	}
	if (asteroid_state == MEDIUM)
	{
		radius = 30.0f * size_factor;
		for (int x = 0; x < figure_points.size(); x++)
		{
			figure_points[x] = size_factor * asteroid_points_state[x];
		}
	}
	if (asteroid_state == SMALL)
	{
		radius = 30.0f * size_factor;
		for (int x = 0; x < figure_points.size(); x++)
		{
			figure_points[x] = size_factor * asteroid_points_state[x];
		}
	}
}

void Asteroid::ChangeSize()
{
	/*this is the changesize code, it have the small to big for the debugging mode, when you can change
	the asteroid size*/
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
	/*assing the random position with the values, for it to be more random if the number is even the
	position is negative, and if it's odd it would be positive*/
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

void Asteroid::AssignPosition(Vector2 position)
{
	origin = position;
}

void Asteroid::DebugLine(const Vector2 player)
{
	/* Draw a line between the player and the asteroid, the identity gets loaded because the asteroid is
	rotating every time and the line has to be fixed to the player, if it's depending on the asteroid it
	will be rotating*/
	glLoadIdentity();
	glBegin(GL_LINE_STRIP);
	glVertex2f(origin.x, origin.y);
	glVertex2f(player.x, player.y);
	glEnd();
}

bool Asteroid::Colide()
{
	return colide;
}

void Asteroid::AssignColide(bool state)
{
	colide = state;
}

bool Asteroid::CloseToShip()
{
	return close_to_ship;
}

void Asteroid::CheckShipDistance(bool state)
{
	close_to_ship = state;
}

bool Asteroid::CloseToBullet()
{
	return close_to_bullet;
}

void Asteroid::CheckBulletDistance(bool state)
{
	close_to_bullet = state;
}