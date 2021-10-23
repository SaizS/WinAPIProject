#pragma once

class SceneManager
{
private:
	static SceneManager* instance;

	map<string, Scene*> totalScene;
	Scene* curScene;

	SceneManager();
	~SceneManager();

public:
	static SceneManager* GetInstance();
	static void Create();
	static void Delete();

	void Update();
	void Render(HDC hdc);

	Scene* Add(string key, Scene* scene);

	void ChangeScene(string key);
};