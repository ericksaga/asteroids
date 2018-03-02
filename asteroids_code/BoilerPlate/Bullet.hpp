#pragma once

#include "Entity.hpp"

const float BULLET_SPEED = 300.0f;
const int MAX_SCREEN_TIME_BULLETS = 80;

class Bullet:public Entity
{
public:
	//functions
	Bullet();
	Bullet(float, Entity*);
	void Update(const float);
	void Render();
	void MoveForward(const float);
	int GetScreenTime();
private:
	void BulletRender();
	//members
	int m_screen_time;
};
