#include "Entity.hpp"

Entity::Entity()
{
	origin = Vector2(0.0f, 0.0f);
	angle_degree = 0.0f;
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

void Entity::Update(const int w_width, const int w_height)
{
	math_master.AngleNormalizeDegree(angle_degree);
	Warp(w_width, w_height);
}

void Entity::Render()
{

}