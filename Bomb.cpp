#include "framework.h"

Bomb::Bomb()
{
	bomb = IMAGE->Add(L"Images/Item/bomb.bmp", 640, 19, 32, 1);
	bombAni = new Animation(bomb, 0.005f);
	bombAni->SetDefault(true);
	rect = new Rect(0, 0, 25, 25);
	speed = 800;
	gravity = 0.0f;
	isActive = false;
	angle = 0.0f;
	land = IMAGE->Add(L"Images/landCollision.bmp", 1176, 224);
	realPos = { 0,0 };
	isBounce = false;
	damage = 10;
}

Bomb::~Bomb()
{
	delete bombAni;
	delete rect;
}

void Bomb::Update()
{
	if (!isActive)
		return;
	else
	{
		rect->pos.x += cos(angle) * speed * DELTATIME;
		rect->pos.y -= sin(angle) * speed * DELTATIME;

		realPos.x += cos(angle) * speed * DELTATIME;


		//angle -= DELTATIME;

		gravity -= GRAVITY*0.5f;

		rect->pos.y -= gravity;

		bombAni->Update();

		if (rect->Bottom() > GetLandY())
		{			
			if (isActive)
				EFFECT->Start("bomb", { rect->pos.x, rect->pos.y - 50 });
			isActive = false;
			speed = 800;
			SOUND->Play("bomb");
		}
	}
}

void Bomb::Render(HDC hdc)
{
	//land->Render(hdc, { WIN_WIDTH*0.5f, WIN_HEIGHT * 0.5f, WIN_WIDTH, WIN_HEIGHT });
	if (isActive)
		bomb->Render(hdc, *rect, bombAni->GetFrame());
	//Rectangle(hdc, rect->Left(), rect->Top(), rect->Right(), rect->Bottom());
}

void Bomb::PlayBomb(float angle, Vector pos, Vector fullPos)
{
	rect->pos = pos;
	this->angle = angle;
	isActive = true;
	isBounce = false;
	gravity = 10.0f;
	realPos = fullPos;
	bombAni->Play();
}

float Bomb::GetLandY()
{
	int x = (int)(realPos.x * (land->GetSize().x / (float)WIN_WIDTH * 0.5f));

	for (int i = (int)realPos.y; i < WIN_HEIGHT; i++)

	{
		int y = i * land->GetSize().y / WIN_HEIGHT;

		COLORREF color = GetPixel(land->GetMemDC(), x, y);

		if (color != MAGENTA)
			return (float)i;
	}

	return (float)WIN_HEIGHT;
}
