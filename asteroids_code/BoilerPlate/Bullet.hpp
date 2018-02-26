#pragma once

#include "Entity.hpp"

const float BULLET_SPEED = 120.0f;
const int MAX_SCREEN_TIME = 120;

class Bullet:public Entity
{
public:
	//functions
	Bullet();
	Bullet(float, Entity*);
	void Update(const int, const int, const float);
	void Render();
	void MoveForward(const float);
	int GetScreenTime();
private:
	void BulletRender();
	//members
	int m_screen_time;
};
