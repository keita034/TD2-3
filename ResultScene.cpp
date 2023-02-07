#include "ResultScene.h"

void ResultScene::Initialize()
{
	input = Input::GetInstance();
	sceneManager = SceneManager::GetInstance();
}

void ResultScene::Update()
{
	// シーンチェンジ
	if (input->TriggerPush(DIK_SPACE))
	{
		sceneManager->ChangeScene("TITLE");
	}
}

void ResultScene::Draw()
{
}

void ResultScene::Finalize()
{
}
