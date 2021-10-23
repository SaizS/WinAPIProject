#pragma once

class GameOver : public Scene
{
private:
	Image* gameover;
	Rect* rect;
	int alpha;

	float endTime;

public:
	GameOver();
	~GameOver();

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};