#pragma once

#include "vector2.hpp"

class player {

	//members
	vector2 origin;

	//functions
public:
	
	player();
	void move(const vector2&);
	void render();

};