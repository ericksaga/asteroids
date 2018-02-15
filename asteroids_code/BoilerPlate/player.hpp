#pragma once

#include <vector>

#include "Vector2.hpp"
#include "mathUtilities.hpp"

const float move_speed = 5.0f;
const float rotation_angle = 3.0f;
class Player {

	//members
	MathUtilities conv;
	Vector2 origin;
	std::vector <Vector2> ship_points;
	std::vector <Vector2> thruster_points;
	float angle_degree;
	float mass;
	bool thruster_on;
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