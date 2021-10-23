#include "framework.h"

Effect::Effect(Image* texture, Vector size, float speed)
	: texture(texture)
{
	ani = new Animation(texture, speed);
	ani->SetDefault();
	ani->SetEndEvent(bind(&Effect::End, this));
	isActive = false;

	rect = new Rect(0.0f, 0.0f, size.x, size.y);
}

Effect::~Effect()
{
	delete ani;
	delete rect;
}

void Effect::Update()
{
	if (!isActive)
		return;

	ani->Update();
}

void Effect::Render(HDC hdc)
{
	if (!isActive)
		return;

	texture->Render(hdc, *rect, ani->GetFrame());
}

void Effect::Start(Vector pos)
{
	rect->pos = pos;
	isActive = true;
	ani->Play();
}

void Effect::End()
{
	isActive = false;
}
