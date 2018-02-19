#pragma once

#include "Entity.hpp"

const float MOVE_SPEED = 5.0f;
const float ROTATION_ANGLE = 3.0f;
class Player :public Entity
{
public:
	//functions
	Player();
	void RotateLeft();
	void RotateRight();
	//-@override
	void Update(const int, const int);
	void MoveForward();
	void Render();
	//@-
private:
	void Ship_Render();
	void Thruster_Render();
	//members
	std::vector <Vector2> thruster_points;
	float mass;
	bool thruster_on;
};