#include "framework.h"

Sky::Sky()
{
	sky = IMAGE->Add(L"Images/BackGround/sky.bmp", 512, 96);
	rect = new Rect(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f, WIN_WIDTH, WIN_HEIGHT);
}

Sky::~Sky()
{
	delete rect;
}

void Sky::Render(HDC hdc)
{
	sky->Render(hdc, *rect);
}
