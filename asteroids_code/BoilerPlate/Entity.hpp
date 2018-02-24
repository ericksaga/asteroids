#pragma once
#include "Vector2.hpp"
#include <vector>

const float SPEED = 3.0f;
const float GRAVITY = 9.8f;
class Entity
{
public:
	//functions
	Entity();
	virtual void Render();
	virtual void Update(const int, const int);
	virtual void MoveForward();
protected:
	void Warp(const int, const int);
	//members
	MathUtilities math_master;
	Vector2 origin;
	Vector2 speed;
	float angle_degree;
	std::vector<Vector2> figure_points;
};