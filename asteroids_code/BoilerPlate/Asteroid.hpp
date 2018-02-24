#pragma once

#include "Entity.hpp"

const float ASTEROID_SPEED = 1.0f;
const float ASTEROID_ROTATION = 1.0f;

class Asteroid:public Entity
{
public:
	//functions
	Asteroid();
	void ChangeSizeForTest();
	int GetSize();
	//@-override
	void MoveForward();
	void Update(const int, const int);
	void Render();
	void AssignOrientation(int);
	void AssignPosition(int, int);
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
	float size_factor;
	size asteroid_state;
	std::vector <Vector2> asteroid_points_state;
};