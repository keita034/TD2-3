#include "TitleScene.h"

void TitleScene::Initialize()
{
	input = Input::GetInstance();

	camera_ = std::make_unique<CinemaCamera>();
	camera_->Initialize();
	userCamera_ = std::make_unique<UserCamera>(1280, 720);

	stage_ = std::make_unique<Stage>();
	stage_->Initialize(camera_.get(), "Resources/SurfaceParts/",
		"Map01", "Map02", "Map03", "Map04",
		"Map05", "Map06", "Map07", "Map08",
		"Map09", "Map010", "Map011", "Map012",
		"Map013", "Map014", "Map015", "Map016",
		"Map017", "Map018", "Map019", "Map020",
		"Map021", "Map022", "Map023", "Map024");

	titleTex_ = TextureManager::GetInstance()->LoadTexture("Resources/title/title.png");
	spriteTitle_.reset(Sprite::Create2DSprite(titleTex_));

	spriteTransform.Initialize();
	spriteTransform.translation = { 640.0f,360.0f,0.0f };
}

void TitleScene::Update()
{
	stage_->SetStageObjScale({ 20.0f,20.0f,20.0f });
	stage_->SetStageFrameScale({ 20.0f,20.0f,20.0f });
	stage_->SetStageFrameTrans({ 0.0f,0.0f,0.0f });

	stage_->SetStageTopTrans({ 10.0f,20.0f,10.0f });
	stage_->SetStageLeftTrans({ 20.0f,10.0f,10.0f });
	stage_->SetStageCenterLeftTrans({ 10.0f,10.0f,20.0f });
	stage_->SetStageCenterRightTrans({ 20.0f,10.0f,10.0f });
	stage_->SetStageRightTrans({ 10.0f,10.0f,20.0f });
	stage_->SetStageBottomTrans({ 10.0f,20.0f,10.0f });


	stage_->Update(camera_.get());

	userCamera_->SetCameraType(cameraType);
	userCamera_->Update();

	camera_->SetTarget(AliceMathF::Vector3(0.0f, 15.0f, 0.0f));

	camera_->SetEye(camera_->GetTarget() + userCamera_->GetEye());
	camera_->SetUp(userCamera_->GetUp());
}

void TitleScene::Draw()
{
	spriteTitle_->Draw(spriteTransform);
	stage_->Draw();
}

void TitleScene::Finalize()
{
}
