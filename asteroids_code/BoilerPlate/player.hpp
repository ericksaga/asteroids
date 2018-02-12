#pragma once

#include "Vector2.hpp"

const float move_speed = 5.0;
const float rotation_angle = 4.0;
class Player {

	//members
	Vector2 origin;
	float angle_degree;
	//functions
	void Ship_Render();
	void Thruster_Render();

public:
	
	Player();
	void MoveForward();
	void RotateLeft();
	void RotateRight();
	void Update(const int w_width, const int w_height);
	void Render();
};