#pragma once

class EffectManager
{
private:
	static EffectManager* instance;
	
	
	//map<string, vector<Effect*>> totalEffect;
	typedef vector<Effect*> Effects;
	map<string, Effects> totalEffect;

	EffectManager();
	~EffectManager();

public:
	static EffectManager* GetInstance();
	static void Create();
	static void Delete();

	void Update();
	void Render(HDC hdc);

	void Add(string key, wstring fileName, int width, int height, int frameX, int frameY, Vector size, COLORREF transColor, int poolCount, float speed = 0.1f);
	void Add(string key, Image* texture, Vector size, int poolCount, float speed = 0.1f);

	void Start(string key, Vector pos);
};