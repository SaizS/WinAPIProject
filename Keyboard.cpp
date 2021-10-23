#include "framework.h"

Keyboard* Keyboard::instance = NULL;

Keyboard::Keyboard()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		keyUp.set(i, false);
		keyDown.set(i, false);
	}
}

Keyboard::~Keyboard()
{
}

Keyboard* Keyboard::GetInstance()
{
	return instance;
}

void Keyboard::Create()
{
	instance = new Keyboard();
}

void Keyboard::Delete()
{
	delete instance;
}

bool Keyboard::KeyDown(DWORD key)
{
	if (GetAsyncKeyState(key))
	{
		if (!keyDown[key])
		{
			keyDown.set(key, true);
			return true;
		}
	}
	else
	{
		keyDown.set(key, false);
	}

	return false;
}

bool Keyboard::KeyUp(DWORD key)
{
	if (GetAsyncKeyState(key))
	{
		keyUp.set(key, true);
	}
	else
	{
		if (keyUp[key])
		{
			keyUp.set(key, false);
			return true;
		}
	}

	return false;
}

bool Keyboard::KeyPress(DWORD key)
{
	if (GetAsyncKeyState(key))
		return true;

	return false;
}
