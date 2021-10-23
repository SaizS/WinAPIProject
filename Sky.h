#pragma once

class Sky
{
private:
	Image* sky;
	Rect* rect;

public:
	Sky();
	~Sky();

	void Render(HDC hdc);

};