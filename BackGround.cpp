#include "framework.h"

BackGround::BackGround()
{
	sky = new Sky();
	land = new Land();
}

BackGround::~BackGround()
{
	delete sky;
	delete land;
}

void BackGround::Update()
{
}

void BackGround::Render(HDC hdc)
{
	sky->Render(hdc);
	land->Render(hdc);
}

void BackGround::MoveMap(float val)
{
	land->MoveMap(val);
}
