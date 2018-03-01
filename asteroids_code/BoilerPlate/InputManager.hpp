#pragma once

#include "Entity.hpp"
#include "Vector2.hpp"
#include <vector>


class InputManager
{
public:
	//funtions
	InputManager();
	//setters
	void SetW(bool);
	void SetA(bool);
	void SetD(bool);
	//getters
	bool GetW();
	bool GetA();
	bool GetD();

private:
	//member
	bool W_KEY;
	bool A_KEY;
	bool D_KEY;


};
