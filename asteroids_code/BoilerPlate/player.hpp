#pragma once

#include "vector2.hpp"
class player {

	//members
	vector2 origin;
	float angle;
	//functions
public:
	
	player();
	void moveforward();
	void rotateleft();
	void rotateright();
	void update();
	void render();

};