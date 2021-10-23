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
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};