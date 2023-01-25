#include "GameMain.h"
#include"SceneFactrory.h"

void GameMain::Initialize()
{
	AliceFramework::Initialize();

	postEffect = std::make_unique<PostEffect>();
	postEffect->PostInitialize();

	//シーンの初期化
	sceneFactory = SceneFactrory::GetInstance();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory);

	SceneManager::GetInstance()->ChangeScene("GAME");
}

void GameMain::Finalize()
{
	AliceFramework::Finalize();
}

void GameMain::Update()
{
	AliceFramework::Update();
}

void GameMain::Draw()
{
	if (input->TriggerPush(DIK_P))
	{
		if (post)
		{
			post = false;
		}
		else
		{
			post = true;
		}
	}
	if (post)
	{
		//描画処理
		postEffect->PreDrawScen();

		sceneManager->Draw();
		imGuiManager->Draw();

		postEffect->PostDrawScen();

		directX12Core->BeginDraw();//描画準備
		postEffect->PostDraw();
		//DirectX毎フレーム処理　ここまで
		directX12Core->EndDraw();//描画後処理
	}
	else
	{
		directX12Core->BeginDraw();//描画準備

		sceneManager->Draw();

		imGuiManager->Draw();

		directX12Core->EndDraw();//描画後処理
	}
}
