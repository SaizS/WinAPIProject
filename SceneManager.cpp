#include "framework.h"

SceneManager* SceneManager::instance = NULL;

SceneManager::SceneManager() : curScene(NULL)
{
}

SceneManager::~SceneManager()
{
	for (auto scene : totalScene)
	{
		delete scene.second;
	}
}

SceneManager* SceneManager::GetInstance()
{
	return instance;
}

void SceneManager::Create()
{
	instance = new SceneManager();
}

void SceneManager::Delete()
{
	delete instance;
}

void SceneManager::Update()
{
	if (curScene == NULL)
		return;

	curScene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (curScene == NULL)
		return;

	curScene->Render(hdc);
}

Scene* SceneManager::Add(string key, Scene* scene)
{
	totalScene.insert({ key, scene });
	return scene;
}

void SceneManager::ChangeScene(string key)
{
	if (totalScene.count(key) == 0)
		return;

	if (totalScene[key] == curScene)
		return;

	if (curScene != NULL)
		curScene->Release();

	curScene = totalScene[key];
	curScene->Init();
}
