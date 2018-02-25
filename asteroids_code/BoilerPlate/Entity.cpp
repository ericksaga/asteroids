#include "Entity.hpp"
//OpenGL include
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Entity::Entity()
{
	origin = Vector2(0.0f, 0.0f);
	angle_degree = 0.0f;
	debugging = false;
}

void Entity::Warp(const int w_width, const int w_height)
{
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
}

void Entity::MoveForward()
{
	float LC_angle_radian = math_master.DegreeToRadian(angle_degree);
	origin += Vector2(-SPEED * sin(LC_angle_radian), SPEED * cos(LC_angle_radian));
}

void Entity::Update(const int w_width, const int w_height, const float delta_time)
{
	math_master.AngleNormalizeDegree(angle_degree);
	Warp(w_width, w_height);
}

void Entity::Render()
{

}

void Entity::RenderCircle()
{
	float LC_2pi = 2 * PI;
	float LC_actual_angle = LC_2pi / 15;
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < 15; x++)
	{
		glVertex2f(
			radius * cos(LC_actual_angle * x), 
			radius * sin(LC_actual_angle * x)
		);
	}
	glEnd();
}

void Entity::ActivateDebugMode()
{
	if (debugging)
	{
		debugging = false;
	}
	else
	{
		debugging = true;
	}
}

Vector2 Entity::GetOrigin()
{
	return origin;
}

float Entity::GetEntityRadius()
{
	return radius;
}
void Entity::ChangeDebuggingState(bool state)
{
	debugging = state;
}
bool Entity::DebuggingState()
{
	return debugging;
}