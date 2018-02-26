#include "Bullet.hpp"
//OpenGL include
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Bullet::Bullet()
{
	origin = Vector2(0.0f, 0.0f);
	angle_degree = 0.0f;
	radius = 7.5f;
	screen_time = 0;
	figure_points.push_back(Vector2(5.0f, 5.0f));
	figure_points.push_back(Vector2(-5.0f, 5.0f));
	figure_points.push_back(Vector2(-5.0f, -5.0f));
	figure_points.push_back(Vector2(5.0f, -5.0f));
}

Bullet::Bullet(float angle, Entity* ship)
{
	origin = ship->GetOrigin();
	angle_degree = angle;
	origin.x += ship->GetEntityRadius() * -sin(math_master.DegreeToRadian(angle_degree));
	origin.y += ship->GetEntityRadius() * cos(math_master.DegreeToRadian(angle_degree));
	radius = 7.5f;
	screen_time = 0;
	figure_points.push_back(Vector2(5.0f, 5.0f));
	figure_points.push_back(Vector2(-5.0f, 5.0f));
	figure_points.push_back(Vector2(-5.0f, -5.0f));
	figure_points.push_back(Vector2(5.0f, -5.0f));
}

void Bullet::MoveForward(const float delta_time)
{
	//calculate speed depending on the size, smallest = fastest
	float LC_angle_radian = math_master.DegreeToRadian(angle_degree);
	float LC_speed_x = BULLET_SPEED * -sin(LC_angle_radian);
	float LC_speed_y = BULLET_SPEED * cos(LC_angle_radian);
	origin += delta_time * Vector2(LC_speed_x, LC_speed_y);
}

void Bullet::Update(const int w_width, const int w_height, const float delta_time)
{
	MoveForward(delta_time);
	Entity::Update(w_width, w_height, delta_time);
	screen_time++;
}

void Bullet::Render()
{
	glLoadIdentity();
	glTranslatef(origin.x, origin.y, 0.0f);
	glRotatef(angle_degree, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	BulletRender();
	if (debugging)
	{
		RenderCircle();
	}
}

void Bullet::BulletRender()
{
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < figure_points.size(); x++)
	{
		glVertex2f(figure_points[x].x, figure_points[x].y);
	}
	glEnd();
}

int Bullet::GetScreenTime()
{
	return screen_time;
}