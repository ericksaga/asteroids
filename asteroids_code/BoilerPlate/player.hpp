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
	void CheckInmortal(const float);
	void ActivateInmortal(const float);
	bool GetInmortal();
	std::vector<Vector2> GetShipPoints();
	//-@override
	void Update(const float);
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
	float m_start_timer;
	int m_inmortal_timer;
	bool m_thruster_on;
	bool m_inmortal_ship;
};