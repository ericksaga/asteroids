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
	virtual void Update(const int, const int, const float);
	virtual void MoveForward();
	void RenderCircle();
	void ActivateDebugMode();
	float GetEntityRadius();
	void ChangeDebuggingState(bool);
	bool DebuggingState();
	Vector2 GetOrigin();
protected:
	//protected functions
	void Warp(const int, const int);
	//members
	MathUtilities math_master;
	Vector2 speed;
	Vector2 origin;
	float angle_degree;
	std::vector<Vector2> figure_points;
	float radius;
	bool debugging;
};