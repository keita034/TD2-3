#include "GameMain.h"
#include"SceneFactrory.h"

void GameMain::Initialize()
{
	AliceFramework::Initialize();

	postEffect = std::make_unique<PostEffect>();
	postEffect->PostInitialize();

	//ƒV[ƒ“‚Ì‰Šú‰»
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
		//•`‰æˆ—
		postEffect->PreDrawScen();

		sceneManager->Draw();
		imGuiManager->Draw();

		postEffect->PostDrawScen();

		directX12Core->BeginDraw();//•`‰æ€”õ
		postEffect->PostDraw();
		//DirectX–ˆƒtƒŒ[ƒ€ˆ—@‚±‚±‚Ü‚Å
		directX12Core->EndDraw();//•`‰æŒãˆ—
	}
	else
	{
		directX12Core->BeginDraw();//•`‰æ€”õ

		sceneManager->Draw();

		imGuiManager->Draw();

		directX12Core->EndDraw();//•`‰æŒãˆ—
	}
}
