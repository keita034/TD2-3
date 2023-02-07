#include "TitleScene.h"

void TitleScene::Initialize()
{
	input = Input::GetInstance();
	sceneManager = SceneManager::GetInstance();

	titleTex_ = TextureManager::GetInstance()->LoadTexture("Resources/title/title.png");
	spriteTitle_.reset(Sprite::Create2DSprite(titleTex_));

	spriteTransform.Initialize();
	spriteTransform.translation = { 640.0f,360.0f,0.0f };
}

void TitleScene::Update()
{
	// シーンチェンジ
	if (input->TriggerPush(DIK_SPACE))
	{
		sceneManager->ChangeScene("GAME");
	}
}

void TitleScene::Draw()
{
	spriteTitle_->Draw(spriteTransform);
}

void TitleScene::Finalize()
{
}
