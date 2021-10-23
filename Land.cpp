#include "framework.h"

Land::Land()
{
	land = IMAGE->Add(L"Images/BackGround/land.bmp", 1176, 224, RGB(248, 0, 248));
	rect = new Rect(WIN_WIDTH, WIN_HEIGHT * 0.5f, WIN_WIDTH * 2.0f, WIN_HEIGHT);
}

Land::~Land()
{
	delete rect;
}

void Land::Render(HDC hdc)
{
	land->Render(hdc, *rect);
}

void Land::MoveMap(float val)
{
	if(rect->Right() > WIN_WIDTH)
		rect->pos.x -= val;
}
