#include "framework.h"

GameOver::GameOver()
{
	gameover = IMAGE->Add(L"Images/Title/GameOver.bmp", 304, 224);
	rect = new Rect(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f, WIN_WIDTH, WIN_HEIGHT);
	alpha = 255;
	endTime = 0.0f;
}

GameOver::~GameOver()
{
	delete rect;
}

void GameOver::Init()
{
}

void GameOver::Update()
{
	if (alpha < 255)
		alpha += 1;
	endTime += 0.1f;
}

void GameOver::Render(HDC hdc)
{
	gameover->Render(hdc, *rect);
	wstring str = L"점수 : " + to_wstring(score);
	if (endTime > 5.0f)
	{
		if (MessageBox(hWnd, str.c_str(), L"게임 종료", MB_OK) == IDOK)
			exit(0);
	}
}

void GameOver::Release()
{
}
