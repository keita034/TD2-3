#include "SceneFactrory.h"
#include "TitleScene.h"
#include"GameScene.h"

SceneFactrory* SceneFactrory::GetInstance()
{
	static SceneFactrory instance;
	return &instance;
}

BaseScene* SceneFactrory::CreateScene(const std::string& sceneName)
{
	//次のシーンを生成
	BaseScene* newScene = nullptr;

	if (sceneName == "TITLE")
	{
		newScene = new TitleScene();
	}
	else if(sceneName == "GAME")
	{
		newScene = new GameScene();
	}
	return newScene;
}
