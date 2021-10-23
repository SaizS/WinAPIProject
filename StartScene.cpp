#include "framework.h"

StartScene::StartScene()
{
	title = IMAGE->Add(L"Images/Title/title.bmp", 1200, 800);
	start = IMAGE->Add(L"Images/Title/start.bmp", 79, 8);

	delayTime = 0;
}

StartScene::~StartScene()
{
}

void StartScene::Init()
{
}

void StartScene::Update()
{
	delayTime += 1;

	if (KEYBOARD->KeyDown('A'))
	{
		SCENE->ChangeScene("Play");
		SOUND->Play("bgm", 0.5f);
	}
}

void StartScene::Render(HDC hdc)
{
	title->Render(hdc, { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f, WIN_WIDTH, WIN_HEIGHT });
	start->Render(hdc, { WIN_WIDTH * 0.48f, WIN_HEIGHT * 0.75f, 400, 100 });
}

void StartScene::Release()
{
}
