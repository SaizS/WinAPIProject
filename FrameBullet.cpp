#include "framework.h"

FrameBullet::FrameBullet()
{
	image[0] = IMAGE->Add(L"Images/Item/RightFrameBullet.bmp", 960, 50, 12, 1);
	ani[0] = new Animation(image[0], 0.05f);
	ani[0]->SetDefault();
	ani[0]->SetEndEvent(bind(&FrameBullet::SetIsActive, this));

	image[1] = IMAGE->Add(L"Images/Item/LeftFrameBullet.bmp", 960, 50, 12, 1);
	ani[1] = new Animation(image[1], 0.05f);
	ani[1]->SetDefaultReverse();
	ani[1]->SetEndEvent(bind(&FrameBullet::SetIsActive, this));

	image[2] = IMAGE->Add(L"Images/Item/UpFrameBullet.bmp", 600, 800, 12, 1);
	ani[2] = new Animation(image[2], 0.05f);
	ani[2]->SetDefault();
	ani[2]->SetEndEvent(bind(&FrameBullet::SetIsActive, this));

	rect = new Rect(0, 0, 250, 100);
	upRect = new Rect(0, 0, 100, 250);
	hitBox = new Rect(0, 0, 0, 0);

	isRight = true;
}

FrameBullet::~FrameBullet()
{
	delete ani[0];
	delete ani[1];
	delete rect;
	delete hitBox;
}

void FrameBullet::Update()
{
	if (!isActive)
		return;
	if (!isUp)
	{
		if (isRight)
		{
			ani[RIGHT]->Update();
			hitBox->SetRect(rect->Left(), rect->Top() + 30, rect->Right() - 30, rect->Bottom());
		}
		else
		{
			ani[LEFT]->Update();
			hitBox->SetRect(rect->Left() + 30, rect->Top() + 30, rect->Right(), rect->Bottom());
		}
	}
	else
	{
		ani[UP]->Update();
		hitBox->SetRect(upRect->Left() + 30, upRect->Top() + 30, upRect->Right() - 30, upRect->Bottom() - 30);
	}
}

void FrameBullet::Render(HDC hdc)
{
	if (!isActive)
		return;

	if (!isUp)
	{
		if (isRight)
			image[RIGHT]->Render(hdc, *rect, ani[RIGHT]->GetFrame());
		else
			image[LEFT]->Render(hdc, *rect, ani[LEFT]->GetFrame());
	}
	else
	{
		image[UP]->Render(hdc, *upRect, ani[UP]->GetFrame());
	}
	//Rectangle(hdc, hitBox->Left(), hitBox->Top(), hitBox->Right(), hitBox->Bottom());
}

void FrameBullet::Fire(Vector pos, bool isRight, bool isUp)
{
	if (!isUp)
		rect->pos = pos;
	else
		upRect->pos = pos;
	this->isRight = isRight;
	this->isUp = isUp;
	isActive = true;

	if (isUp)
	{
		ani[UP]->Play();
		hitBox->SetRect(upRect->Left() + 30, upRect->Top() + 30, upRect->Right() - 30, upRect->Bottom() - 30);
	}
	else
	{
		if (isRight)
		{
			ani[RIGHT]->Play();
			hitBox->SetRect(rect->Left(), rect->Top() + 30, rect->Right() - 30, rect->Bottom());
		}
		else
		{
			ani[LEFT]->Play();
			hitBox->SetRect(rect->Left() + 30, rect->Top() + 30, rect->Right(), rect->Bottom());
		}
	}
}

void FrameBullet::SetIsActive()
{
	isActive = false;
}

int FrameBullet::GetFrame()
{
	if (isRight)
	{
		return ani[RIGHT]->GetFrame().x;
	}
	else
	{
		return ani[LEFT]->GetFrame().x;
	}
}
