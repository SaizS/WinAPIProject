#pragma once

class ScoreHub
{
private:
	Image* scoreHub;
	Rect* rect;

	vector<Image*> numbers;

	vector<Image*> scoreNum;
	vector<Rect*> scoreRect;

	vector<Image*> lifeNumbers;
	Image* lifeNum;
	Rect* lifeRect;

public:
	ScoreHub();
	~ScoreHub();

	void Update();
	void Render(HDC hdc);

	void InitNumber();
	void SetScore();
	void SetLife(int life);
};