#include "GameMain.h"
#include"SceneFactrory.h"

void GameMain::Initialize()
{
	AliceFramework::Initialize();

	postEffect = std::make_unique<PostEffect>();
	postEffect->PostInitialize();

	//�V�[���̏�����
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
		//�`�揈��
		postEffect->PreDrawScen();

		sceneManager->Draw();
		imGuiManager->Draw();

		postEffect->PostDrawScen();

		directX12Core->BeginDraw();//�`�揀��
		postEffect->PostDraw();
		//DirectX���t���[�������@�����܂�
		directX12Core->EndDraw();//�`��㏈��
	}
	else
	{
		directX12Core->BeginDraw();//�`�揀��

		sceneManager->Draw();

		imGuiManager->Draw();

		directX12Core->EndDraw();//�`��㏈��
	}
}
