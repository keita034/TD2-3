#include "GameScene.h"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

void GameScene::Initialize()
{
	input = Input::GetInstance();
	mesh2D = Mesh::GetInstance();

	//ライト初期化
	light.reset(Light::Create());
	light->SetLightColor(lightColor);
	//モデルにライトをセット
	Model::SetLight(light.get());

	camera = std::make_unique<CinemaCamera>();
//	camera->SetEye({ -27.0000000f, 226.199310f, -241.000000f });
//	camera->SetTarget({ 0.0f, 85.1993027f, 0.0f });
	camera->Initialize();

	userCamera = new UserCamera(1280, 640);

	stage = std::make_unique<Stage>();

	stage->Initialize();
}

void GameScene::Update()
{
	AliceMathF::Vector3 move = { 0.0f,0.0f,0.0f };

	camera->MovePosition(move);

	userCamera->Update();
	camera->SetEye(camera->GetTarget() + userCamera->GetEye());
	camera->SetUp(userCamera->GetUp());

	if (Input::GetInstance()->TriggerPush(DIK_RSHIFT))
	{
		stage->FieldPlaneFoldStart(Left, FoldIndex::Beside);
	}

	if (Input::GetInstance()->TriggerPush(DIK_LSHIFT))
	{
		stage->FieldPlaneFoldStart(Left, FoldIndex::Vertical);
	}

	if (Input::GetInstance()->TriggerPush(DIK_RIGHT))
	{
		stage->FieldPlaneFoldStart(Top, FoldIndex::Beside);
	}

	if (Input::GetInstance()->TriggerPush(DIK_LEFT))
	{
		stage->FieldPlaneFoldStart(Top, FoldIndex::Vertical);
	}

	if (Input::GetInstance()->TriggerPush(DIK_UP))
	{
		stage->FieldPlaneFoldStart(CenterLeft, FoldIndex::Beside);
	}

	if (Input::GetInstance()->TriggerPush(DIK_DOWN))
	{
		stage->FieldPlaneFoldStart(CenterLeft, FoldIndex::Vertical);
	}

	stage->Update(camera.get());
}

void GameScene::Draw()
{
	stage->Draw();
}

GameScene* GameScene::GetInstance()
{
	static GameScene instance;
	return &instance;
}
