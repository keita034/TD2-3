#include "Skydome.h"

void Skydome::Initialize(uint32_t modelHandle)
{
	model_ = std::make_unique<Model>();
	model_->SetModel(modelHandle);

	transform_.Initialize();

	float scale = 800.0f;

	transform_.scale = { scale,scale,scale };
}

void Skydome::Update(Camera* camera)
{
	transform_.TransUpdate(camera);
}

void Skydome::Draw()
{
	model_->Draw(transform_);
}
