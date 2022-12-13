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
	camera->Initialize();

	gameCamera_ = std::make_unique<GameCamera>();
	gameCamera_->SetEye({ 0.0f,50.0f,-70.0f });
	gameCamera_->Initialize(UpdateProjMatrixFunc_Perspective);

	modelHandl = Model::CreateObjModel("Resources/Player");
	stageModelHandle_ = Model::CreateObjModel("Resources/MainStage");

	stage_ = std::make_unique<Stage>();
	stage_->Initialize(stageModelHandle_);

	model = std::make_unique<Model>();
	model->SetModel(modelHandl);

	//プレーヤー作成
	player_ = new Player(modelHandl);
	player_->Initialise();

	modelTrans.Initialize();
	stageModelTrans_.Initialize();
}

void GameScene::Update()
{
	stage_->Update(gameCamera_.get());
	modelTrans.TransUpdate(gameCamera_.get());
	player_->Update(gameCamera_.get());

#pragma region カメラ位置(デバック用)
	// デバック用:1で真上から,2で斜め上から,3で真横から
	if (input->TriggerPush(DIK_1))
	{
		gameCamera_->SetEye({ 0.0f,100.0f,-1.0f });
	}
	else if (input->TriggerPush(DIK_2))
	{
		gameCamera_->SetEye({ 0.0f,50.0f,-70.0f });
	}
	else if (input->TriggerPush(DIK_3))
	{
		gameCamera_->SetEye({ 0.0f,0.0f,-100.0f });
	}
#pragma endregion
}

void GameScene::Draw()
{
	stage_->Draw();
	//model->Draw(&modelTrans);
	player_->Draw();
}