#include "framework.h"

Sword::Sword()
{
	image = IMAGE->Add(L"Images/Enemy/Enemy - Sword.bmp", 432, 36, 12, 1);
	ani = new Animation(image, 0.05f);
	rect = new Rect(0, 0, 60, 60);

	angle = 0.0f;
	speed = 100.0f;
	gravity = 0.0f;

	isActive = false;
	isLast = false;

	pos = { 0,0 };
}

Sword::~Sword()
{
	delete ani;
	delete rect;
}

void Sword::Update()
{
	if (!isActive)
		return;

	if (!isLast)
	{
		rect->pos.x += cos(angle) * speed * DELTATIME;
		rect->pos.y -= sin(angle) * speed * DELTATIME;

		gravity -= GRAVITY * DELTATIME;
		rect->pos.y -= gravity;
	}
	ani->Update();

	if (rect->pos.y > WIN_HEIGHT - 100)
	{
		isActive = false;
	}

	pos.x = rect->pos.x + moveDistance;
}

void Sword::Render(HDC hdc)
{
	if (!isActive)
		return;
	image->Render(hdc, *rect, ani->GetFrame());
	//Rectangle(hdc, rect->Left()+20, rect->Top() + 10, rect->Right()-20, rect->Bottom()-10);
}

void Sword::Play(Vector pos, float angle, float gravity)
{
	isActive = true;
	isLast = false;
	rect->pos = pos;
	this->angle = angle;
	this->gravity = gravity;
	ani->Play();
	ani->SetPart(0, 10, true);
}

float Sword::GetLandY()
{
	int x = (int)(pos.x * (land->GetSize().x / WIN_WIDTH * 0.5f));

	for (int i = (int)rect->pos.y; i < WIN_HEIGHT; i++)
	{
		int y = i * land->GetSize().y / WIN_HEIGHT;

		COLORREF color = GetPixel(land->GetMemDC(), x, y);

		if (color != MAGENTA)
			return (float)i;
	}
	return (float)WIN_HEIGHT;
}

Rect Sword::GetRect()
{
	Rect rc;
	rc.SetRect( rect->Left() + 20, rect->Top() + 10, rect->Right() - 20, rect->Bottom() - 10 );
	return rc;
}
