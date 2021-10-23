#include "framework.h"

Bullet::Bullet()
{
	image[0] = IMAGE->Add(L"Images/Item/bullet.bmp", 24, 10);
	image[1] = IMAGE->Add(L"Images/Item/bulletUp.bmp", 10, 24);
	rect[0] = new Rect(0, 0, 24, 10);
	rect[1] = new Rect(0, 0, 10, 24);
	speed = 15.0f;
	damage = 1;

	isActive = false;
	isRight = true;
	isUp = false;
}

Bullet::~Bullet()
{
	delete rect[0];
	delete rect[1];
}

void Bullet::Update()
{
	if (!isActive)
		return;

	if (!isUp)
	{
		if (isRight)
			rect[0]->pos.x += speed;
		else
			rect[0]->pos.x -= speed;
	}
	else
	{
		rect[1]->pos.y -= speed;
	}
	if (rect[0]->pos.x >= WIN_WIDTH || rect[0]->pos.x <= 0 || rect[1]->pos.y < 0)
		isActive = false;
}

void Bullet::Render(HDC hdc)
{
	if (!isActive)
		return;
	if (!isUp)
		image[0]->Render(hdc, *rect[0]);
	else
		image[1]->Render(hdc, *rect[1]);
}

void Bullet::Fire(Vector pos, bool Right, bool Up)
{
	rect[0]->pos = pos;
	rect[1]->pos = pos;
	isActive = true;
	isRight = Right;
	isUp = Up;
}

Rect Bullet::GetRect()
{
	if (isUp)
		return *rect[1];
	else
		return *rect[0];
}
