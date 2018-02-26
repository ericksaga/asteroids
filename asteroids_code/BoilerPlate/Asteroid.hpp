#pragma once

#include "Entity.hpp"

const float ASTEROID_SPEED = 40.0f;
const float ASTEROID_ROTATION = 1.0f;
const int MAX_SPAWN_POSITION = 201;
const int MIN_SPAWN_POSITION = 100;
const float RADIUS = 30.0f;

class Asteroid:public Entity
{
public:
	//functions
	Asteroid();
	Asteroid(int);
	void ChangeSize();
	int GetSize();
	void DebugLine(const Vector2);
	void AssignPosition(int, int);
	bool Colide();
	void AssignColide(bool);
	bool CloseToShip();
	void CheckShipDistance(bool);
	bool CloseToBullet();
	void CheckBulletDistance(bool);
	//@-override
	void MoveForward(const float);
	void Update(const int, const int, const float);
	void Render();
	void AssignOrientation(int);
	void AssignPosition(Vector2);
	//-@
	//enumerator
	enum size {
		SMALL = 2,
		MEDIUM = 3,
		BIG = 4
	};
private:
	//private funtions
	void RenderAsteroid();
	void MeasureSizeFactor();
	//members
	float m_auto_rotate;
	size m_asteroid_state;
	float m_size_factor;
	bool m_colide;
	bool m_close_to_ship;
	bool m_close_to_bullet;
	std::vector <Vector2> m_asteroid_points_state;
};