#include "framework.h"

TankBullet::TankBullet()
{
	image[0] = IMAGE->Add(L"Images/Enemy/TankLeft/Tank - Bullet.bmp", 200, 24, 4, 1);
	ani[0] = new Animation(image[0], 0.08f);
	ani[0]->SetDefault(true);
	ani[0]->Play();

	image[1] = IMAGE->Add(L"Images/Enemy/TankRight/Tank - Bullet.bmp", 200, 24, 4, 1);
	ani[1] = new Animation(image[1], 0.08f);
	ani[1]->SetDefaultReverse(true);
	ani[1]->Play();

	rect = new Rect(0, 0, 80, 50);
	speed = 1.0f;
	isRight = false;
}

TankBullet::~TankBullet()
{
	delete ani[0];
	delete ani[1];
	delete rect;
}

void TankBullet::Update()
{
	if (!isActive)
		return;

	if (isRight)
	{
		ani[1]->Update();
		rect->pos.x += speed;
	}
	else
	{
		ani[0]->Update();
		rect->pos.x -= speed;
	}

	if (rect->pos.x < 0)
		isActive = false;
}

void TankBullet::Render(HDC hdc)
{
	if (!isActive)
		return;
	if (!isRight)
		image[0]->Render(hdc, *rect, ani[0]->GetFrame());
	else
		image[1]->Render(hdc, *rect, ani[1]->GetFrame());
}

void TankBullet::Fire(Vector pos, bool isRight)
{
	rect->pos = pos;
	isActive = true;
	this->isRight = isRight;
}
