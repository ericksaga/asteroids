#include "InputManager.hpp"

InputManager::InputManager()
{
	W_KEY = false;
	A_KEY = false;
	D_KEY = false;
}

void InputManager::SetW(bool value)
{
	W_KEY = value;
}

void InputManager::SetA(bool value)
{
	A_KEY = value;
}

void InputManager::SetD(bool value)
{
	D_KEY = value;
}

bool InputManager::GetW()
{
	return W_KEY;
}

bool InputManager::GetA()
{
	return A_KEY;
}

bool InputManager::GetD()
{
	return D_KEY;
}
