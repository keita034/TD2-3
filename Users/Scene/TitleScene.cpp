#include "TitleScene.h"

void TitleScene::Initialize()
{
	input = Input::GetInstance();

	camera_ = std::make_unique<CinemaCamera>();
	camera_->Initialize();
	modelCamera_ = std::make_unique<GameCamera>();
	modelCamera_->Initialize(UpdateProjMatrixFunc_Perspective);
	userCamera_ = std::make_unique<UserCamera>(1280, 720);

	stage_ = std::make_unique<Stage>();
	stage_->Initialize(camera_.get());

	uint32_t handl = AliceModel::CreateModel("Resources/Kaede");

	aliceModel = std::make_unique<AliceModel>();
	aliceModel->SetModel(handl);

	handl = AliceMotionData::CreateMotion("Resources/Kaede/title");
	walkMotion = std::make_unique<AliceMotionData>();
	walkMotion->SetMotion(handl);

	titleTex_ = TextureManager::GetInstance()->LoadTexture("Resources/title/title.png");
	spriteTitle_.reset(Sprite::Create2DSprite(titleTex_));

	spriteTransform.Initialize();
	fbxTransform.Initialize();
	fbxTransform.rotation = { 0.0f,-90.0f * AliceMathF::Deg2Rad,-25.0f * AliceMathF::Deg2Rad };
	spriteTransform.translation = { 640.0f,360.0f,0.0f };

	translation = { -50.0f,-75.0f,0.0f };

	start = { -300.0f,-15.0f,-50.0f };
	end = { 300.0f,-15.0f,-105.0f };

	time = 0;
}

void TitleScene::Update()
{
	frame += 0.017f;
	time += 1;

	stage_->SetStageObjScale({ 20.0f,20.0f,20.0f });

	stage_->SetStageTopTrans({ 10.0f,20.0f,10.0f });
	stage_->SetStageLeftTrans({ 20.0f,10.0f,10.0f });
	stage_->SetStageCenterLeftTrans({ 10.0f,10.0f,20.0f });
	stage_->SetStageCenterRightTrans({ 20.0f,10.0f,10.0f });
	stage_->SetStageRightTrans({10.0f,10.0f,20.0f});
	stage_->SetStageBottomTrans({ 10.0f,20.0f,10.0f });


	stage_->Update(camera_.get());

	userCamera_->SetCameraType(cameraType);
	userCamera_->Update();

	modelCamera_->Update();

	camera_->SetTarget(AliceMathF::Vector3(0.0f, 15.0f, 0.0f));
	modelCamera_->SetTarget(AliceMathF::Vector3(0.0f, 15.0f, 0.0f));
	modelCamera_->SetEye(AliceMathF::Vector3(-25.7979298f, 98.3741608f, -200.953384f));

	camera_->SetEye(camera_->GetTarget() + userCamera_->GetEye());
	camera_->SetUp(userCamera_->GetUp());

	//fbxTransform.translation = { translation.x,translation.y,translation.z };
	fbxTransform.scale = { 0.3f,0.3f,0.3f };
	fbxTransform.TransUpdate(modelCamera_.get());
	
	aliceModel->AnimationUpdate(walkMotion.get(), frame);

	fbxTransform.translation = AliceMathF::Lerp(start, end, time/600);

	if (time >= 600)
	{
		time = 0;
	}
}

void TitleScene::Draw()
{
	spriteTitle_->Draw(spriteTransform);
	stage_->Draw();
	aliceModel->Draw(&fbxTransform);
}

void TitleScene::Finalize()
{
}
