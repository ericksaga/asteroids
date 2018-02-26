#pragma once

#include "Entity.hpp"

const float MOVE_SPEED = 60.0f;
const float ROTATION_ANGLE = 3.0f;
class Player :public Entity
{
public:
	//functions
	Player();
	void RotateLeft();
	void RotateRight();
	//-@override
	void Update(const int, const int, const float);
	void MoveForward();
	void Render();
	//@-
	//public members
	bool dead;
private:
	//private funtions
	void Ship_Render();
	void Thruster_Render();
	//members
	std::vector <Vector2> m_thruster_points;
	float m_mass;
	bool m_thruster_on;
};