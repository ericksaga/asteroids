#pragma once
#include "Vector2.hpp"
#include <vector>

const float SPEED = 3.0f;
const float GRAVITY = 9.8f;
const int LINE_AMOUNT = 15;
class Entity
{
public:
	//functions
	Entity();
	virtual void Render();
	virtual void Update(const float);
	virtual void MoveForward();
	void RenderCircle();
	void UpdateWarp(const int, const int);
	void ActivateDebugMode();
	void ChangeDebuggingState(bool);
	float GetEntityRadius();
	float GetEntityAngle();
	bool DebuggingState();
	Vector2 GetOrigin();
protected:
	//protected functions
	void Warp();
	//members
	MathUtilities m_math_master;
	Vector2 m_speed;
	Vector2 m_origin;
	float m_angle_degree;
	float m_radius;
	std::vector<Vector2> m_figure_points;
	int m_width;
	int m_height;
	bool m_debugging;
};