#pragma once

#include "Entity.hpp"

const float ASTEROID_SPEED = 40.0f;
const float ASTEROID_ROTATION = 1.0f;

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
	//@-override
	void MoveForward(const float);
	void Update(const int, const int, const float);
	void Render();
	void AssignOrientation(int);
	void AssignPosition(Vector2);
	//-@
	//enumerator
	enum size {
		SMALL = 1,
		MEDIUM = 2,
		BIG = 4
	};
private:
	//private funtions
	void RenderAsteroid();
	void SizeRefactor();
	//members
	float auto_rotate;
	size asteroid_state;
	float size_factor;
	bool colide;
	bool close_to_ship;
	std::vector <Vector2> asteroid_points_state;
};