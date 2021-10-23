#include "framework.h"

ItemBullet::ItemBullet()
{
	for (int i = 0; i < 4; i++)
	{
		image[i] = IMAGE->Add(L"Images/Item/ItemBullet.bmp", 45, 6);
		rect[i] = new Rect(0, 0, 45, 6);
		isActive[i] = false;
		angle[i] = 0.0f;
	}

	delayTime = 0.0f;	
	speed = 500;
	isFire = false;
}

ItemBullet::~ItemBullet()
{
	for (Rect* rc : rect)
		delete rc;
}

void ItemBullet::Update()
{
	if (!isFire)
		return;

	delayTime += 0.1f;

	if (delayTime > 0.5f)
	{
		isActive[1] = true;
	}
	if (delayTime > 1.0f)
	{
		isActive[2] = true;
	}
	if (delayTime > 1.5f)
	{
		isActive[3] = true;
		delayTime = 0.0f;

	}

	if (isActive[0])
	{
		rect[0]->pos.x += cos(angle[0]) * speed * DELTATIME;
		rect[0]->pos.y -= sin(angle[0]) * speed * DELTATIME;
	}
	if (isActive[1])
	{
		rect[1]->pos.x += cos(angle[0]) * speed * DELTATIME;
		rect[1]->pos.y -= sin(angle[0]) * speed * DELTATIME;
	}
	if (isActive[2])
	{
		rect[2]->pos.x += cos(angle[0]) * speed * DELTATIME;
		rect[2]->pos.y -= sin(angle[0]) * speed * DELTATIME;
	}
	if (isActive[3])
	{
		rect[3]->pos.x += cos(angle[0]) * speed * DELTATIME;
		rect[3]->pos.y -= sin(angle[0]) * speed * DELTATIME;
	}

	for (int i = 0; i < 4; i++)
	{
		if (rect[i]->Left() > WIN_WIDTH)
		{
			isActive[i] = false;
		}
	}

	if (isFire)
	{
		if (!isActive[0] && !isActive[1] && !isActive[2] && !isActive[3])
			isFire = false;
	}
}

void ItemBullet::Render(HDC hdc)
{
	if (!isFire)
		return;
	for (int i = 0; i < 4; i++)
	{
		if(isActive[i])
			image[i]->Render(hdc, *rect[i]);
	}
}

void ItemBullet::Fire(Vector pos)
{
	for (Rect* rc : rect)
		rc->pos = pos;

	isFire = true;

	for (int i = 0; i < 4; i++)
	{
		int randNum = Math::Random(0, 5);
		switch (randNum)
		{
		case 0:
			angle[i] = 0.0698132;
			break;
		case 1:
			angle[i] = 0.0349066;
			break;
		case 2:
			angle[i] = 0;
			break;
		case 3:
			angle[i] = 6.24828;
			break;
		case 4:
			angle[i] = 6.21337;
			break;
		default:
			break;
		}
	}
	isActive[0] = true;
}

void ItemBullet::Setting()
{
	
}
