#pragma once

#include <vector>
#include "vector2.hpp"
#include "MathUtilities.hpp"

const float asteroid_speed = 1.0f;
const float asteroid_rotation = 1.0f;
class Asteroids
{
	//functions
public:
	Asteroids();
	Asteroids(Vector2&, float);
	void Render();
	void Move();
	void Update(const int, const int);
	void ChangeSize();
	//enumerator
	enum size {
		SMALL = 1,
		MEDIUM = 2,
		BIG = 4
	};
private:
	//members
	float angle_degree;
	float auto_rotate;
	size asteroid_state;
	Vector2 origin;
	std::vector <Vector2> asteroids_points;
	std::vector <Vector2> asteroids_points_state;
	MathUtilities math_master;

};