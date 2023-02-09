#include "ResultScene.h"

void ResultScene::Initialize()
{
	input = Input::GetInstance();

	tex = TextureManager::GetInstance()->LoadTexture("Resources/resultSerial.png");
	sprite.reset(Sprite::Create2DSprite(tex));
	transform.Initialize();
	transform.translation = { 640.0f,360.0f,0.0f };
}

void ResultScene::Update()
{
}

void ResultScene::Draw()
{
	sprite->Draw(transform);
}

void ResultScene::Finalize()
{
}
