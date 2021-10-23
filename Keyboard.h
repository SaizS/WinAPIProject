#pragma once

#define KEYMAX 255

class Keyboard
{
private:
	static Keyboard* instance;

	bitset<KEYMAX> keyUp;
	bitset<KEYMAX> keyDown;

	Keyboard();
	~Keyboard();
public:
	static Keyboard* GetInstance();
	static void Create();
	static void Delete();

	bool KeyDown(DWORD key);
	bool KeyUp(DWORD key);
	bool KeyPress(DWORD key);
};