#pragma once

class StartScene : public Scene
{
private:
	Image* title;
	Image* start;

	int delayTime;

public:
	StartScene();
	~StartScene();
	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};