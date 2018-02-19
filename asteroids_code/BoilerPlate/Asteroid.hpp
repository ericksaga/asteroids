#pragma once

#include "Entity.hpp"

const float ASTEROID_SPEED = 1.0f;
const float ASTEROID_ROTATION = 1.0f;
class Asteroid:public Entity
{
public:
	//functions
	Asteroid();
	Asteroid(Vector2&, float);
	void ChangeSizeForTest();
	int GetSize();
	//@-override
	void MoveForward();
	void Update(const int, const int);
	void Render();
	//-@
	//enumerator
	enum size {
		SMALL = 1,
		MEDIUM = 2,
		BIG = 4
	};
private:
	//members
	float auto_rotate;
	size asteroid_state;
	std::vector <Vector2> asteroid_points_state;

};