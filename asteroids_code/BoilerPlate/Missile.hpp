#pragma once

#include "Entity.hpp"

const float MISSILE_SPEED = 150.0f;
const int MAX_SCREEN_TIME_MISSILES = 80;

class Missile :public Entity
{
public:
	//functions
	Missile();
	Missile(float, Entity*);
	void Update(const float);
	void Render();
	void MoveForward(const float);
	int GetScreenTime();
	std::vector<Vector2> GetMissilePoints();
private:
	void MissileRender();
	//members
	int m_screen_time;
};