#include "framework.h"

BombItem::BombItem()
{
	image = IMAGE->Add(L"Images/Item/BombItem.bmp", 192, 32, 6, 1);
	ani = new Animation(image, 0.08f);
	ani->SetDefault(true);
	rect = new Rect(0, 0, 64, 64);
}

BombItem::~BombItem()
{
	delete ani;
	delete rect;
}

void BombItem::Update()
{
	if (!isActive)
		return;
	ani->Update();
}

void BombItem::Render(HDC hdc)
{
	if (!isActive)
		return;
	image->Render(hdc, *rect, ani->GetFrame());
}

void BombItem::SetIsActiveFalse()
{
	isActive = false;
}

void BombItem::SetIsActiveTrue(Vector pos)
{
	rect->pos = pos;
	isActive = true;
	ani->Play();
}

bool BombItem::Eat(Rect rc)
{
	if (!isActive)
		return false;

	float minX = min(rc.Right(), rect->Right());
	float maxX = max(rc.Left(), rect->Left());

	float minY = min(rc.Bottom(), rect->Bottom());
	float maxY = max(rc.Top(), rect->Top());

	Vector pos;
	pos.x = minX - maxX;
	pos.y = minY - maxY;

	if (pos.x > 0 && pos.y > 0)
	{
		SOUND->Play("EatBomb");
		isActive = false;
		return true;
	}
	return false;
}
