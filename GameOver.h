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

	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};