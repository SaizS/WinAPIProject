#include "framework.h"

FrameItem::FrameItem()
{
	image = IMAGE->Add(L"Images/Item/FlameItem.bmp", 20, 18);
	rect = new Rect(0, 0, 40, 36);
	isActive = false;
}

FrameItem::~FrameItem()
{
	delete rect;
}

void FrameItem::Render(HDC hdc)
{
	if (!isActive)
		return;

	image->Render(hdc, *rect);
}

void FrameItem::SetIsActiveTrue(Vector pos)
{
	//SOUND->Play("EatFrame");
	rect->pos = pos; 
	isActive = true;
}

bool FrameItem::Eat(Rect rc)
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
		SOUND->Play("EatFrame");
		isActive = false;
		return true;
	}
	return false;
}
