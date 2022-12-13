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

	modelHandl = Model::CreateObjModel("Resources/F-15");
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
	stage_->Update(camera.get());
	modelTrans.TransUpdate(camera.get());
	player_->Update(camera.get());
}

void GameScene::Draw()
{
	stage_->Draw();
	//model->Draw(&modelTrans);
	player_->Draw();
}